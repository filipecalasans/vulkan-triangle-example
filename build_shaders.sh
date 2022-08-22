#/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

BUILD_DIR="${SCRIPT_DIR}/build"

if [[ -z "${VULKAN_SDK}" ]]; then
    # Adds required Vulkan tools to PATH
    bash "${VULKAN_ROOT}/setup-env.sh"
fi

mkdir -p "${BUILD_DIR}/shaders"

glslc "${SCRIPT_DIR}/shaders/simple_shader.frag" -o "${BUILD_DIR}/shaders/simple_shader.frag.spv"
glslc "${SCRIPT_DIR}/shaders/simple_shader.vert" -o "${BUILD_DIR}/shaders/simple_shader.vert.spv"

