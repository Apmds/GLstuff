#version 330 core

layout (location = 0) in vec3 aPos; // Hardcoded location
in vec3 color;

uniform float horizontalShift;

out vec3 outPosition;

void main() {
   outPosition = vec3(aPos.x + horizontalShift, aPos.y, aPos.z);
   gl_Position = vec4(outPosition, 1.0);
}