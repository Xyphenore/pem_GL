#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

// Passage des matrices de transformation
uniform mat4 model;
uniform mat4 world;

// Matrice caméra
uniform mat4 view;

// Matrice normalisée, projettant les objets
uniform mat4 projection;


out vec3 vertexColor;

void main() {
    gl_Position = projection * view * world * model * vec4(aPos, 1.0f);

    vertexColor = color;
}
