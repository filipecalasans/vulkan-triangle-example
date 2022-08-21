#/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

BUILD_DIR="${SCRIPT_DIR}/build"

if [[ -z "${VULKAN_ROOT}" ]]; then
    VULKAN_VERSION="1.3.216.0"
    VULKAN_ROOT="${HOME}/VulkanSDK/${VULKAN_VERSION}/"    
fi

# Adds required Vulkan tools to PATH
source "${VULKAN_ROOT}/setup-env.sh"

mkdir -p "${BUILD_DIR}/shaders"

glslc "${SCRIPT_DIR}/shaders/simple_shader.frag" -o "${BUILD_DIR}/shaders/simple_shader.frag.spv"
glslc "${SCRIPT_DIR}/shaders/simple_shader.vert" -o "${BUILD_DIR}/shaders/simple_shader.vert.spv"

