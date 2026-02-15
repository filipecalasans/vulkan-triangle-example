#/usr/bin/env bash

if [[ ! -z "${VULKAN_SDK}" ]]; then
    echo "Vulkan Env. identified!"
else 
    if [[ -z "${VULKAN_ROOT}" ]]; then
        VULKAN_SDK_BASE="${HOME}/VulkanSDK"
        VULKAN_ROOT=$(find "${VULKAN_SDK_BASE}" -maxdepth 1 -mindepth 1 -type d | sort -V | tail -n 1)
        if [[ -z "${VULKAN_ROOT}" ]]; then
            echo "Error: No Vulkan SDK version found in ${VULKAN_SDK_BASE}" >&2
            return 1 2>/dev/null || exit 1
        fi
        echo "Detected Vulkan SDK: $(basename "${VULKAN_ROOT}")"
    fi
    pushd "${VULKAN_ROOT}"
    # Adds required Vulkan tools to PATH
    source "./setup-env.sh" || popd
    popd
fi

echo "Vulkan SDK: ${VULKAN_SDK}"