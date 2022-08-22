#/usr/bin/env bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

source "${SCRIPT_DIR}/set-vulkan-env.sh"

BUILD_DIR="${SCRIPT_DIR}/build"
(cd "${BUILD_DIR}" && ./lve)