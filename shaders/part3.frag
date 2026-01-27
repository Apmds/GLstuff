#version 330 core

in vec2 texOutCoords;

out vec4 fragColor;

uniform sampler2D bgTex;
uniform sampler2D fgTex;

void main() {
    vec4 bgColor = texture(bgTex, texOutCoords);
    vec4 fgColor = texture(fgTex, texOutCoords);
    fragColor = mix(bgColor, fgColor, 0.2);
}