#version 330 core

layout (location = 0) in vec3 vertPos;
layout (location = 1) in vec3 vertColor;
layout (location = 2) in vec2 texCoords;

out vec3 vertOutColor;
out vec2 texOutCoords;

void main() {
    vertOutColor = vertColor;
    texOutCoords = texCoords;
    gl_Position = vec4(vertPos, 1.0);
}