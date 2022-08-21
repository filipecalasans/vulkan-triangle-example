#version 450

layout (location = 0) out vec4 outAtt0;
layout (location = 0) in vec3 vertexColor;

void main() {
    outAtt0 = vec4(vertexColor, 1.0);
}