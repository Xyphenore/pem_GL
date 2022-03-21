#version 330 core

in vec2 vertexTexture;
in vec3 vertexPosition;
in vec3 vertexNormal;

uniform sampler2D textureFrag;

layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = texture( textureFrag, vertexTexture);
}
