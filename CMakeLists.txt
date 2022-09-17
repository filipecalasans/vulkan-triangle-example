cmake_minimum_required(VERSION 3.1)
project(little_vulkan C CXX)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

set(CMAKE_CXX_STANDARD 17)

option(LVE_ENABLE_PORTABILITY_EXTENSION "Enable Vulkan Portability Extension" OFF)

# Create Exectuables and Libraries
add_executable(lve)
add_library(tiny_obj_loader STATIC)

# Source Files lve
target_sources(lve PRIVATE 
    main.cpp
    first_app.cpp
    keyboard_movement_controller.cpp
    lve_camera.cpp
    lve_device.cpp 
    lve_model.cpp
    lve_pipeline.cpp
    lve_renderer.cpp
    lve_swap_chain.cpp
    lve_window.cpp
    simple_render_system.cpp
)

# Source Files tinyobjloader
target_sources(tiny_obj_loader PRIVATE 
    third_party/tinyobjloader/tiny_obj_loader.cc)

# Includes lve
target_include_directories(lve PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(lve PUBLIC ${GLM_INCLUDE_DIRS})
target_include_directories(lve PRIVATE third_party)
# Includes tiny_obj_loader
target_include_directories(tiny_obj_loader PRIVATE third_party/tiny_obj_loader)

# Linked Libraries lve
target_link_libraries(lve glfw Vulkan::Vulkan tiny_obj_loader)

if(LVE_ENABLE_PORTABILITY_EXTENSION)
    target_compile_definitions(lve PUBLIC LVE_ENABLE_PORTABILITY_EXTENSION)
endif(LVE_ENABLE_PORTABILITY_EXTENSION)

add_custom_command(
  TARGET lve POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/models/
    $<TARGET_FILE_DIR:lve>/models/)