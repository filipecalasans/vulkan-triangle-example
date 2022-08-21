#/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

BUILD_DIR="${SCRIPT_DIR}/build"

if [[ -z "${VULKAN_VERSION}" ]]; then
    VULKAN_VERSION="1.3.216.0"
fi

VULKAN_ROOT="${HOME}/VulkanSDK/${VULKAN_VERSION}/"
GLSLC="${VULKAN_ROOT}/macOS/bin/glslc"

mkdir -p "${BUILD_DIR}/shaders"

"${GLSLC}" "${SCRIPT_DIR}/shaders/simple_shader.frag" -o "${BUILD_DIR}/shaders/simple_shader.frag.spv"
"${GLSLC}" "${SCRIPT_DIR}/shaders/simple_shader.vert" -o "${BUILD_DIR}/shaders/simple_shader.vert.spv"

