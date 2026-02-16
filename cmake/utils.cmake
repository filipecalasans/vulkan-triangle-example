find_program(GLSLC_EXECUTABLE glslc HINTS Vulkan::glslc)

# target_compile_shaders(<target>
#     SOURCES <shader1> [<shader2> ...]
#     [OUTPUT_DIR <dir>]
# )
#
# Compiles GLSL shader sources into SPIR-V (.spv) using glslc.
# Shaders are only recompiled when their source files change.
#
# Arguments:
#   TARGET     - The build target that depends on the compiled shaders.
#   SOURCES    - List of GLSL shader source files (.vert, .frag, .comp, etc.).
#   OUTPUT_DIR - Directory for the compiled .spv files.
#                Defaults to ${CMAKE_CURRENT_BINARY_DIR}/shaders.
#
# Example:
#   target_compile_shaders(my_app
#       SOURCES
#           ${CMAKE_SOURCE_DIR}/shaders/simple_shader.vert
#           ${CMAKE_SOURCE_DIR}/shaders/simple_shader.frag
#       OUTPUT_DIR
#           $<TARGET_FILE_DIR:my_app>/shaders
#   )
function(target_compile_shaders TARGET)
    set(options "")
    set(oneValueArgs OUTPUT_DIR)
    set(multiValueArgs SOURCES)
    cmake_parse_arguments(SHADER "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT SHADER_OUTPUT_DIR)
        set(SHADER_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")
    endif()

    foreach(SHADER_SOURCE ${SHADER_SOURCES})
        if(NOT IS_ABSOLUTE "${SHADER_SOURCE}")
            set(SHADER_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_SOURCE}")
        endif()
        get_filename_component(SHADER_NAME "${SHADER_SOURCE}" NAME)
        set(SHADER_OUTPUT "${SHADER_OUTPUT_DIR}/${SHADER_NAME}.spv")

        add_custom_command(
            OUTPUT "${SHADER_OUTPUT}"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${SHADER_OUTPUT_DIR}"
            COMMAND ${GLSLC_EXECUTABLE} "${SHADER_SOURCE}" -o "${SHADER_OUTPUT}"
            DEPENDS "${SHADER_SOURCE}"
            COMMENT "Compiling shader ${SHADER_NAME}"
        )

        list(APPEND SHADER_OUTPUTS "${SHADER_OUTPUT}")
    endforeach()

    add_custom_target(${TARGET}_shaders ALL DEPENDS ${SHADER_OUTPUTS})
    add_dependencies(${TARGET} ${TARGET}_shaders)
endfunction()
