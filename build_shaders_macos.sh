#/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

BUILD_DIR="${SCRIPT_DIR}/build"

VULKAN_ROOT="${HOME}/VulkanSDK/1.3.204.0/"
GLSLC="${VULKAN_ROOT}/macOS/bin/glslc"

mkdir -p "${BUILD_DIR}/shaders"

"${GLSLC}" "${SCRIPT_DIR}/shaders/simple_shader.frag" -o "${BUILD_DIR}/shaders/simple_shader.frag.spv"
"${GLSLC}" "${SCRIPT_DIR}/shaders/simple_shader.vert" -o "${BUILD_DIR}/shaders/simple_shader.vert.spv"

