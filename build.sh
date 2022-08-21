#/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

BUILD_DIR="${SCRIPT_DIR}/build"
mkdir -p "${BUILD_DIR}"

CMAKE_FLAGS=()


if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "Enable Portability" 
    CMAKE_FLAGS+=("-DLVE_ENABLE_PORTABILITY_EXTENSION=ON")
fi

"${SCRIPT_DIR}/build_shaders_macos.sh"
(cd "${BUILD_DIR}" && cmake "${CMAKE_FLAGS[@]}" ../ -G "Ninja" && ninja -j3)