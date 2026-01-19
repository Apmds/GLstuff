#version 330 core

in vec3 outPosition;
out vec4 FragColor;

uniform float transparency;

void main() {
    FragColor = vec4(outPosition, transparency);
}