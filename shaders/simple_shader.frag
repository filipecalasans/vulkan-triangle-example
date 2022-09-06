#version 450

layout (location = 0) out vec4 outAtt0;

layout (push_constant) uniform Push {
    mat2 transformation;
    vec2 offset;
    vec3 color;
} push;

void main() {
    outAtt0 = vec4(push.color, 1.0);
}