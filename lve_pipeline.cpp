#include "lve_pipeline.h"

// std
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace lve {

LvePipeline::LvePipeline(
    LveDevice& device, 
    const std::string& vertFilepath,
    const std::string& fragFilepath,
    const PipelineConfigInfo& configInfo) 
    : lveDevice(device)
{
  createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
}

LvePipeline::~LvePipeline()
{
  vkDestroyShaderModule(lveDevice.device(), vertShaderModule, nullptr);
  vkDestroyShaderModule(lveDevice.device(), fragShaderModule, nullptr);
  vkDestroyPipeline(lveDevice.device(), graphicsPipeline, nullptr);
}

std::vector<char> LvePipeline::readFile(const std::string& filepath)
{
  std::ifstream file{filepath, std::ios::ate | std::ios::binary};

  if (!file.is_open()) {
    throw std::runtime_error("failed to open file: " + filepath);
  }

  const size_t fileSize = static_cast<size_t>(file.tellg());
  assert(fileSize != 0 && "Files is empty");
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);
  file.close();
  return buffer;
}

void LvePipeline::createGraphicsPipeline(
    const std::string& vertFilepath, 
    const std::string& fragFilepath, 
    const PipelineConfigInfo& configInfo) 
{
  assert(
    configInfo.pipelineLayout != VK_NULL_HANDLE && 
    "Cannot create graphics pipeline:: no pipelineLayour provided in configInfo");
  assert(
    configInfo.renderPass != VK_NULL_HANDLE && 
    "Cannot create graphics pipeline:: no renderPass provided in configInfo");
    
  auto vertCode = readFile(vertFilepath);
  auto fragCode = readFile(fragFilepath);

  createShaderModule(vertCode, &vertShaderModule);
  createShaderModule(fragCode, &fragShaderModule);

  VkPipelineShaderStageCreateInfo shaderStages[] = {
    {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_VERTEX_BIT,
      .module = vertShaderModule,
      .pName = "main",
      .flags = 0,
      .pNext = nullptr,
      .pSpecializationInfo = nullptr,
    },
    {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = fragShaderModule,
      .pName = "main",
      .flags = 0,
      .pNext = nullptr,
      .pSpecializationInfo = nullptr,
    },
  };

  VkPipelineVertexInputStateCreateInfo vertexInputInfo{
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexAttributeDescriptionCount = 0,
    .vertexBindingDescriptionCount = 0,
    .pVertexAttributeDescriptions = nullptr,
    .pVertexBindingDescriptions = nullptr,
  };

  VkGraphicsPipelineCreateInfo pipelineInfo{
    .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
    .stageCount = 2,
    .pStages = shaderStages,
    .pVertexInputState = &vertexInputInfo,
    .pInputAssemblyState = &configInfo.inputAssemblyInfo,
    .pViewportState = &configInfo.viewportInfo,
    .pRasterizationState = &configInfo.rasterizationInfo,
    .pMultisampleState = &configInfo.multisampleInfo,
    .pColorBlendState = &configInfo.colorBlendInfo,
    .pDepthStencilState = &configInfo.depthStencilInfo,
    // .pDynamicState = &dynamicState,
    .pDynamicState = nullptr,
    
    .layout = configInfo.pipelineLayout,
    .renderPass = configInfo.renderPass,
    .subpass = configInfo.subpass,

    .basePipelineIndex = -1,
    .basePipelineHandle = VK_NULL_HANDLE,
  };

  if (vkCreateGraphicsPipelines(lveDevice.device(), VK_NULL_HANDLE, 
          1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
    throw std::runtime_error("failed to create graphics pipeline!");
  }
}

void LvePipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule)
{
  VkShaderModuleCreateInfo createInfo{
    .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .codeSize = code.size(),
    .pCode = reinterpret_cast<const std::uint32_t*>(code.data()),
  };

  if (vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
    throw std::runtime_error("failed to create shader module!");
  }
}

void LvePipeline::bind(VkCommandBuffer commandBuffer) 
{
  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
}

void LvePipeline::defaultPipelineConfigInfo(PipelineConfigInfo& configInfo, std::uint32_t width, std::uint32_t height)
{
  configInfo.viewport = {
    .x = 0.0f,
    .y = 0.0f,
    .width = static_cast<float>(width),
    .height = static_cast<float>(height),
    .minDepth = 0.0,
    .maxDepth = 1.0f,
  };

  configInfo.scissor = {
    .offset = {0, 0},
    .extent = {width, height},
  };

  configInfo.inputAssemblyInfo = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
    .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
    .primitiveRestartEnable = VK_FALSE,
  };

  configInfo.rasterizationInfo = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .depthClampEnable = VK_FALSE,
    .rasterizerDiscardEnable = VK_FALSE,
    .polygonMode = VK_POLYGON_MODE_FILL,
    .lineWidth = 1.0f,
    .cullMode = VK_CULL_MODE_NONE,
    .frontFace = VK_FRONT_FACE_CLOCKWISE,
    .depthBiasEnable = VK_FALSE,
    .depthBiasConstantFactor = 0.0f,  // Optional
    .depthBiasClamp = 0.0f,           // Optional
    .depthBiasSlopeFactor = 0.0f,     // Optional
  };
  configInfo.multisampleInfo = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
    .sampleShadingEnable = VK_FALSE,
    .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
    .minSampleShading = 1.0f,           // Optional
    .pSampleMask = nullptr,             // Optional
    .alphaToCoverageEnable = VK_FALSE,  // Optional
    .alphaToOneEnable = VK_FALSE,       // Optional
  };
  configInfo.colorBlendAttachment = {
    .colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT |
      VK_COLOR_COMPONENT_A_BIT,
    .blendEnable = VK_FALSE,
    .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,   // Optional
    .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,  // Optional
    .colorBlendOp = VK_BLEND_OP_ADD,              // Optional
    .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,   // Optional
    .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,  // Optional
    .alphaBlendOp = VK_BLEND_OP_ADD,              // Optional
  };
  configInfo.depthStencilInfo = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable = VK_TRUE,
    .depthWriteEnable = VK_TRUE,
    .depthCompareOp = VK_COMPARE_OP_LESS,
    .depthBoundsTestEnable = VK_FALSE,
    .minDepthBounds = 0.0f,         // Optional
    .maxDepthBounds = 1.0f,         // Optional
    .stencilTestEnable = VK_FALSE,
    .front = {},                    // Optional
    .back = {},                     // Optional
  }; 

  configInfo.colorBlendInfo = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable = VK_FALSE,
    .logicOp = VK_LOGIC_OP_COPY,  // Optional
    .attachmentCount = 1,
    .pAttachments = &configInfo.colorBlendAttachment,
    .blendConstants[0] = 0.0f,  // Optional
    .blendConstants[1] = 0.0f,  // Optional
    .blendConstants[2] = 0.0f,  // Optional
    .blendConstants[3] = 0.0f,  // Optional
  };

  configInfo.viewportInfo = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
    .viewportCount = 1,
    .pViewports = &configInfo.viewport,
    .scissorCount = 1,
    .pScissors = &configInfo.scissor,
    .pNext = nullptr,
    .flags = 0,
  };
}

}  // namespace lve 