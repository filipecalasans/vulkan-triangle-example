#ifndef LVE_FRAME_INFO
#define LVE_FRAME_INFO

namespace lve {

struct LveFrameInfo {
    int frameIndex;
    float frameTime;
    VkCommandBuffer commandBuffer;
    LveCamera& camera;
};

} // namespace lve

#endif