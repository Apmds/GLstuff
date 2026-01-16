#version 330 core

layout (location = 0) in vec3 aPos; // Hardcoded location
in vec3 color;
out vec3 Color;

void main() {
   Color = color;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}