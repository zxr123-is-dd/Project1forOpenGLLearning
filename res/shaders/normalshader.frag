#version 330 core

out vec4 FragColor;

in vec2 ourTexCoords;
in vec3 ourNormal;
in vec3 FragPos;

uniform vec3 viewPos;

void main() {
    vec3 viewDir = viewPos - FragPos;
    if (dot(viewDir, ourNormal) > 0) {
        FragColor = vec4(0.6, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(0.0, 0.0, 0.6, 1.0);
    }
}