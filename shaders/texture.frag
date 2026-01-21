#version 330 core

in vec3 vertOutColor;
in vec2 texOutCoords;

out vec4 fragColor;

uniform sampler2D texture1; // The texture for the container
uniform sampler2D texture2; // The texture for the face
uniform float mixValue;

void main() {
    vec4 contColor = texture(texture1, texOutCoords);
    vec4 faceColor = texture(texture2, vec2(-texOutCoords.x, texOutCoords.y));
    fragColor = mix(contColor, faceColor, mixValue) /** vec4(vertOutColor, 1.0)*/;
}