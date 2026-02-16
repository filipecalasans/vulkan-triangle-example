cmake_minimum_required(VERSION 3.23)
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

# Header Files lve
target_sources(lve PRIVATE
    FILE_SET lve_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        first_app.h
        keyboard_movement_controller.h
        lve_buffer.h
        lve_camera.h
        lve_device.h
        lve_frame_info.h
        lve_game_object.h
        lve_input_source.h
        lve_model.h
        lve_nativewindow.h
        lve_pipeline.h
        lve_render.h
        lve_swap_chain.h
        lve_utils.h
        lve_windowfactory.h
        simple_render_system.h
)

set_target_properties(lve PROPERTIES VERIFY_INTERFACE_HEADER_SETS ON)

# Source Files tinyobjloader
target_sources(tiny_obj_loader PRIVATE 
    third_party/tinyobjloader/tiny_obj_loader.cc)

# Includes lve
target_include_directories(lve PUBLIC ${GLM_INCLUDE_DIRS})
target_include_directories(lve PRIVATE third_party)

# Linked Libraries lve
target_link_libraries(lve Vulkan::Vulkan tiny_obj_loader)

if(LVE_USE_GLFW)
    find_package(glfw3 3.3 REQUIRED)
    target_include_directories(lve PUBLIC ${GLFW_INCLUDE_DIRS})
    target_sources(lve PRIVATE
        lve_window.cpp
        lve_glfw_input_source.cpp
    )
    target_sources(lve PRIVATE
        FILE_SET lve_headers
        TYPE HEADERS
        FILES
            lve_window.h
            lve_glfw_input_source.h
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