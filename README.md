# Vulkan Tutorial 

Vulkan tutorial that teaches on how to build Little Vulkan Engine (LVE), a game engine built from
scratch using Vulkan.

This code-base is based on following tuorial series: 

https://www.youtube.com/watch?v=Y9U9IE0gVHA&t=0s

Tutorial Repo: https://github.com/blurrypiano/littleVulkanEngine

License: MIT


# Pre-requisites

You need to install the following dependencies in order to be able to build this projects:

## Build Tools

* CMake
* Ninja

## Dependencies

* VulkanSDK 1.3.216 or grater.
* glfw
* glm

# How To Build & Run

It is worth noting that the scripts provided will default the Vulkan to
version `1.3.216` if you don't provide `VULKAN_ROOT` environment variable.

```sh
VULKAN_ROOT=$HOME/VulkanSDK/<VERSION> source ./set-vulkan-env.sh
./build.sh
./run-dev.sh
```