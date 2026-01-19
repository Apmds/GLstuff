#version 330 core

layout (location = 0) in vec3 aPos; // Hardcoded location
in vec3 color;

uniform float horizontalShift;

out vec3 Color;

void main() {
   Color = color;
   gl_Position = vec4(aPos.x + horizontalShift, -aPos.y, aPos.z, 1.0);
}