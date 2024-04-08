#pragma once

#include "lve_device.h"
#include "lve_swap_chain.h"
#include "lve_nativewindow.h"

//std
#include <cassert>
#include <memory>
#include <vector>

/**
 * 
 * Renderer encapsulates the Swap Chain management, command buffer
 * lifecycle, and drawing frames steps. 
 * 
 */
namespace lve {

class LveRenderer
{
public:

    LveRenderer(LveNativeWindow& lveWindow, LveDevice& device);
    
    ~LveRenderer();

    LveRenderer(const LveRenderer&) = delete;
    LveRenderer &operator=(const LveRenderer&) = delete;

    VkRenderPass getSwapChainRenderPass() const { return lveSwapChain->getRenderPass(); }
    bool isFrameInProgress() const { return isFrameStarted; }
    
    VkCommandBuffer getCurrentCommandBuffer() const { 
        assert(isFrameStarted && "Cannot get command buffer when frame not in progress.");
        return commandBuffers[currentFrameIndex]; 
    }

    int getFrameIndex() const {
        assert(isFrameStarted && "Cannot get frame index when frame not in progress");
        return currentFrameIndex;
    }

    float getAspectRatio() const {
        return lveSwapChain->extentAspectRatio();
    }

    VkCommandBuffer beginFrame();
    void endFrame();
    void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
    void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

private:

    void createCommandBuffers();
    void freeCommandBuffers();

    void createSyncObjects();
    void recreateSwapChain();

    LveNativeWindow& lveWindow;
    LveDevice& lveDevice;
    std::unique_ptr<LveSwapChain> lveSwapChain;
    std::vector<VkCommandBuffer> commandBuffers;

    uint32_t currentImageIndex{0};
    int currentFrameIndex{0};
    bool isFrameStarted{false};
};

}