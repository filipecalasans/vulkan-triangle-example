#version 450

layout (location = 0) out vec3 vertexColor;
layout (location = 0) in vec2 position;

void main() {
    gl_Position = vec4(position, 0.0, 1.0);
    vertexColor = vec3(1.0, 0.0, 0.0);
}