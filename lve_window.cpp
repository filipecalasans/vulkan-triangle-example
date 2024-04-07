#include "lve_window.h"

//std
#include <stdexcept>
#include <vector>

namespace lve {

#define GLFW_WINDOW(w) (reinterpret_cast<GLFWwindow*>(w))

LveWindow::LveWindow(int w, int h, std::string name) : LveNativeWindow(w, h, std::move(name)) {
    initWindow();
}

LveWindow::~LveWindow() {
    glfwDestroyWindow(GLFW_WINDOW(window));
    glfwTerminate();
}

void LveWindow::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(GLFW_WINDOW(window), this);
    glfwSetFramebufferSizeCallback(GLFW_WINDOW(window), framebufferResizeCallback);
}

std::vector<const char *> LveWindow::getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    return extensions;
}

bool LveWindow::shouldClose() {
    return glfwWindowShouldClose(GLFW_WINDOW(window));
}

void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface /* out */) {
    if (glfwCreateWindowSurface(instance, GLFW_WINDOW(window), nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface");
    }
}

void LveWindow::waitForEvents() {
    glfwWaitEvents();
}

void LveWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto lveWindow = reinterpret_cast<LveWindow*>(glfwGetWindowUserPointer(window));
    lveWindow->frameBufferResized = true;
    lveWindow->width = width;
    lveWindow->height = height;
}

} // namesapce lve