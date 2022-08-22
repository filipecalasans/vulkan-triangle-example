cmake_minimum_required(VERSION 3.1)
project(little_vulkan C CXX)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

set(CMAKE_CXX_STANDARD 17)

option(LVE_ENABLE_PORTABILITY_EXTENSION "Enable Vulkan Portability Extension" OFF)

# Create Exectuable
add_executable(lve)

# Source Files
target_sources(lve PRIVATE 
    main.cpp
    lve_model.cpp
    lve_pipeline.cpp
    lve_window.cpp
    first_app.cpp  
    lve_device.cpp  
    lve_swap_chain.cpp
)

# Includes
target_include_directories(lve PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(lve PUBLIC ${GLM_INCLUDE_DIRS})

# Linked Libraries
target_link_libraries(lve glfw Vulkan::Vulkan)

if(LVE_ENABLE_PORTABILITY_EXTENSION)
    target_compile_definitions(lve PUBLIC LVE_ENABLE_PORTABILITY_EXTENSION)
endif(LVE_ENABLE_PORTABILITY_EXTENSION)