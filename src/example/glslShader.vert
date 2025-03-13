#version 450

layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec3 outPosition;

void main() {
    outPosition = inPosition;
}