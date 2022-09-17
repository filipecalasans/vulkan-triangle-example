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
#include <string>
#include <memory>
#include <vector>

namespace lve {

class LveModel final {
    public:

        struct Vertex {
            glm::vec3 position{};
            glm::vec3 color{};
            glm::vec3 normal{};
            glm::vec2 uv{};

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        
            bool operator==(const Vertex& other) const {
                return position == other.position && 
                    color == other.color &&
                    normal == other.normal &&
                    uv == other.uv;
            }
        };

        struct Builder {
            std::vector<Vertex> vertices{};
            std::vector<uint32_t> indices{};

            void loadModel(const std::string& filepath);
        };
        
        LveModel(LveDevice& device, const LveModel::Builder& builder);
        ~LveModel();

        LveModel(const LveModel&) = delete;
        LveModel &operator=(const LveModel&) = delete;

        static std::unique_ptr<LveModel> createModelFromFile(
            LveDevice& device, const std::string& filepath);

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

    private:
        void createVertexBuffer(const std::vector<Vertex>& vertices);
        void createIndexBuffer(const std::vector<uint32_t>& indices);

        LveDevice& lveDevice;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
        
        bool hasIndexBuffer = false;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;
        uint32_t indexCount;
};

} // namespace lve
#endif