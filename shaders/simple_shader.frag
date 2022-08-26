#version 450

layout (location = 0) out vec4 outAtt0;
layout (location = 0) in vec3 fragColor;

void main() {
    outAtt0 = vec4(fragColor, 1.0);
}