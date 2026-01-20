#version 330 core

in vec3 vertOutColor;
in vec2 texOutCoords;

out vec4 fragColor;

uniform sampler2D tex; // The texture

void main() {
    fragColor = texture(tex, texOutCoords) * vec4(vertOutColor, 1.0);
}