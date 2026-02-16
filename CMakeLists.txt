cmake_minimum_required(VERSION 3.1)
project(little_vulkan C CXX)
enable_testing()

include(cmake/utils.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_package(glm REQUIRED)

set(CMAKE_CXX_STANDARD 17)

option(LVE_USE_GLFW "Use GLW to interact with the native window system" OFF)

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
    simple_render_system.cpp
    lve_buffer.cpp
    lve_input_source.cpp
)

# Source Files tinyobjloader
target_sources(tiny_obj_loader PRIVATE 
    third_party/tinyobjloader/tiny_obj_loader.cc)

# Includes lve
target_include_directories(lve PUBLIC ${GLEW_INCLUDE_DIRS})
target_include_directories(lve PUBLIC ${GLM_INCLUDE_DIRS})
target_include_directories(lve PRIVATE third_party)

# Linked Libraries lve
target_link_libraries(lve Vulkan::Vulkan tiny_obj_loader)

if(LVE_USE_GLFW)
    find_package(glfw3 3.3 REQUIRED)
    target_sources(
        lve PRIVATE 
        lve_window.cpp
        lve_glfw_input_source.cpp
    )
    target_compile_definitions(lve PUBLIC GLFW_XPLAT_DESKTOP)
    target_link_libraries(lve glfw)
endif(LVE_USE_GLFW)

target_compile_shaders(lve
      SOURCES
        shaders/simple_shader.vert
        shaders/simple_shader.frag
  )

add_custom_command(
  TARGET lve POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/models/
    $<TARGET_FILE_DIR:lve>/models/)