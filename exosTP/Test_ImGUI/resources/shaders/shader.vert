#version 330 //core

layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in vec3 aNormal;

out vec2 vertexTexture;
out vec3 vertexNormal;
out vec3 vertexPosition;

void main() {
    vertexPosition = aPos;
    gl_Position = vec4(vertexPosition, 1.0f);

    vertexNormal = aNormal;
    vertexTexture = aTexture;
}
