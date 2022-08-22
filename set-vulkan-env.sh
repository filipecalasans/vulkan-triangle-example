#/usr/bin/env bash

if [[ ! -z "${VULKAN_SDK}" ]]; then
    echo "Vulkan Env. identified!"
else 
    if [[ -z "${VULKAN_ROOT}" ]]; then
        VULKAN_VERSION="1.3.216.0"
        VULKAN_ROOT="${HOME}/VulkanSDK/${VULKAN_VERSION}/"    
    fi
    pushd "${VULKAN_ROOT}"
    # Adds required Vulkan tools to PATH
    source "./setup-env.sh" || popd
    popd
fi

echo "Vulkan SDK: ${VULKAN_SDK}"