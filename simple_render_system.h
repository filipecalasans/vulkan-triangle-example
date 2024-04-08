#pragma once

#include "lve_camera.h"
#include "lve_device.h"
#include "lve_game_object.h"
#include "lve_pipeline.h"
#include "lve_swap_chain.h"
#include "lve_frame_info.h"

// vulkan headers
#include <vulkan/vulkan.h>

//std
#include <cassert>
#include <memory>
#include <vector>

namespace lve {

class SimpleRenderSystem
{
public:
    SimpleRenderSystem(LveDevice& device, VkRenderPass renderPass);
    ~SimpleRenderSystem();

    SimpleRenderSystem(const SimpleRenderSystem&) = delete;
    SimpleRenderSystem &operator=(const SimpleRenderSystem&) = delete;

    void renderGameObjects(
        LveFrameInfo& frameInfo,
        std::vector<LveGameObject>& gameObjects);

private:

    void createPipelineLayout();
    void createPipeline(VkRenderPass renderPass);
    void createSyncObjects();
    
    LveDevice& lveDevice;

    std::unique_ptr<LvePipeline> lvePipeline;
    VkPipelineLayout pipelineLayout;
};

}