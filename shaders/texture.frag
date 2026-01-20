#version 330 core

in vec3 vertOutColor;
in vec2 texOutCoords;

out vec4 fragColor;

uniform sampler2D texture1; // The texture
uniform sampler2D texture2; // The texture

void main() {
    fragColor = mix(texture(texture1, texOutCoords), texture(texture2, texOutCoords), 0.2) /** vec4(vertOutColor, 1.0)*/;
}