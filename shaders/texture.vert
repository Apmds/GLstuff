#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertColor;

out vec3 vertOutColor;

void main() {
    vertOutColor = vertColor;
    gl_Position = vec4(vertPos, 1.0);
}