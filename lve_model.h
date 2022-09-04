#ifndef LVE_MODEL_HH
#define LVE_MODEL_HH

#include "lve_device.h"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

// vulkan headers
#include <vulkan/vulkan.h>

// std
#include <vector>

namespace lve {

class LveModel final {
    public:

        struct Vertex {
            glm::vec2 position;
            glm::vec3 color;
            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        LveModel(LveDevice& device, const std::vector<Vertex>& vertices);
        ~LveModel();

        LveModel(const LveModel&) = delete;
        LveModel &operator=(const LveModel&) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffer(const std::vector<Vertex>& vertices);

        LveDevice& lveDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
};

} // namespace lve
#endif