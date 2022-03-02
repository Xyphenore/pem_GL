#version 330 core

in vec3 vertexColor;

uniform vec3 lightColor;

out vec4 fragColor;

void main() {
    float ambientStrength = 0.1f;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 result = lightColor * vertexColor;
    fragColor = vec4( result, 1.0f);
}
