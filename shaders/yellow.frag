#version 330 core

in vec3 Color;
out vec4 FragColor;

uniform float transparency;

void main() {
    FragColor = vec4(1.0, 1.0, 0.0, transparency);
}