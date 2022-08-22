#/usr/bin/env bash

if [[ ! -z "${VULKAN_SDK}" ]]; then
    echo "Vulkan Env. identified!"
    exit 0
fi

if [[ -z "${VULKAN_ROOT}" ]]; then
    VULKAN_VERSION="1.3.216.0"
    VULKAN_ROOT="${HOME}/VulkanSDK/${VULKAN_VERSION}/"    
fi

# Adds required Vulkan tools to PATH
source "${VULKAN_ROOT}/setup-env.sh"