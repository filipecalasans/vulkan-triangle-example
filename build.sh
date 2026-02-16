#/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

BUILD_DIR="${SCRIPT_DIR}/build"
mkdir -p "${BUILD_DIR}"

CMAKE_FLAGS=()

CMAKE_FLAGS+=("-DLVE_USE_GLFW=ON")

source "${SCRIPT_DIR}/set-vulkan-env.sh"
"${SCRIPT_DIR}/build_shaders.sh"
(cd "${BUILD_DIR}" && cmake "${CMAKE_FLAGS[@]}" ../ -G "Ninja" && ninja -j3)