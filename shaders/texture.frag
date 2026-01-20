#version 330 core

in vec3 vertOutColor;

out vec4 fragColor;

void main() {
    fragColor = vec4(vertOutColor, 1.0);
}