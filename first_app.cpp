#include "first_app.h"

#include "keyboard_movement_controller.h"
#include "lve_camera.h"
#include "lve_model.h"
#include "simple_render_system.h"
#include "lve_windowfactory.h"
#include "lve_buffer.h"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <chrono>
#include <memory>
#include <numeric>
#include <stdexcept>

namespace lve {

struct GlobalUbo {
  alignas(16) glm::mat4 projectionView{1.0f};
  alignas(16) glm::vec3 lightDirection = glm ::normalize(glm::vec3{1.f, -3.f, -1.f});
};

FirstApp::FirstApp() :
  lveWindow(createNativeWindow(WIDTH, HEIGHT, "Hellp Vulkan")),
  lveDevice(*lveWindow),
  lveRenderer(*lveWindow, lveDevice) {
  loadGameObjects();
}

FirstApp::~FirstApp() { }

void FirstApp::run() {

  std::vector<std::unique_ptr<LveBuffer>> uboBuffers(LveSwapChain::MAX_FRAMES_IN_FLIGHT);
  for (int i = 0; i < uboBuffers.size(); i++) {
    uboBuffers[i] = std::make_unique<LveBuffer>(
      lveDevice,
      sizeof(GlobalUbo),
      1,
      VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
      VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT /*| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT*/);
    uboBuffers[i]->map();
  }

  SimpleRenderSystem simpleRenderSystem{lveDevice, lveRenderer.getSwapChainRenderPass()};
  LveCamera camera{};
  auto viewerObject = LveGameObject::createGameObject();
  KeyboardMovementController cameraController{};

  auto currentTime = std::chrono::high_resolution_clock::now();
  while (!lveWindow->shouldClose()) {
    glfwPollEvents();

    auto newTime = std::chrono::high_resolution_clock::now();
    auto frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
    currentTime = newTime;

    // TODO: Make input cross platform.
    cameraController.moveInPlaneXZ(reinterpret_cast<GLFWwindow*>(lveWindow->getNativeWindow()), frameTime, viewerObject);
    camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

    float aspect = lveRenderer.getAspectRatio();
    // camera.setOrthographicProjection(-aspect, aspect, -1, 1, -1, 1);
    camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);

    if (auto commandBuffer = lveRenderer.beginFrame()) {
      int frameIndex = lveRenderer.getFrameIndex();
      LveFrameInfo frameInfo = {
        .frameIndex = frameIndex,
        .frameTime = frameTime,
        .commandBuffer = commandBuffer,
        .camera = camera,
      };

      // update 
      GlobalUbo ubo{};
      ubo.projectionView = camera.getProjection() * camera.getView();
      uboBuffers[frameIndex]->writeToBuffer(&ubo);
      uboBuffers[frameIndex]->flush();

      // render
      lveRenderer.beginSwapChainRenderPass(commandBuffer);
      simpleRenderSystem.renderGameObjects(frameInfo, gameObjects);
      lveRenderer.endSwapChainRenderPass(commandBuffer);
      lveRenderer.endFrame();

    }
  }

  vkDeviceWaitIdle(lveDevice.device());
}

void FirstApp::loadGameObjects() {    
    std::shared_ptr<LveModel> lveModel = 
        LveModel::createModelFromFile(lveDevice, "models/smooth_vase.obj");
    auto gameObj = LveGameObject::createGameObject();
    gameObj.model = lveModel;
    gameObj.transform.translation = {-.5f, 0.5f, 2.5f};
    gameObj.transform.scale = glm::vec3{3.f, 1.5f, 3.f};
    gameObjects.push_back(std::move(gameObj));
}

}  // namespace lve
