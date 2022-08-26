#ifndef LVE_PIPELINE_H_
#define LVE_PIPELINE_H_

#include "lve_device.h"

#include <string>
#include <vector>

namespace lve {
    
struct PipelineConfigInfo {
  PipelineConfigInfo(const PipelineConfigInfo&) = delete;
  PipelineConfigInfo() = default;
  PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

  VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
  VkPipelineRasterizationStateCreateInfo rasterizationInfo;
  VkPipelineMultisampleStateCreateInfo multisampleInfo;
  VkPipelineColorBlendAttachmentState colorBlendAttachment;
  VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
  VkPipelineLayout pipelineLayout = nullptr;
  VkRenderPass renderPass = nullptr;
  VkPipelineColorBlendStateCreateInfo colorBlendInfo;
  VkPipelineViewportStateCreateInfo viewportInfo;
  std::vector<VkDynamicState> dynamicStateEnables;
  VkPipelineDynamicStateCreateInfo dynamicStateInfo;
  uint32_t subpass = 0;
};
 
class LvePipeline {
 public:
  LvePipeline(
      LveDevice& device,
      const std::string& vertFilepath,
      const std::string& fragFilepath,
      const PipelineConfigInfo& configInfo);

  ~LvePipeline();

  LvePipeline(const LvePipeline&) = delete;
  LvePipeline operator=(const LvePipeline&) = delete;

  void bind(VkCommandBuffer commandBuffer);
  static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

 private:

  static std::vector<char> readFile(const std::string& filepath);
  
  void createGraphicsPipeline(
      const std::string& vertFilepath,
      const std::string& fragFilepath,
      const PipelineConfigInfo& configInfo);

  void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

  LveDevice &lveDevice;
  VkPipeline graphicsPipeline;
  VkShaderModule vertShaderModule;
  VkShaderModule fragShaderModule;
};
}  // namespace lve 

#endif