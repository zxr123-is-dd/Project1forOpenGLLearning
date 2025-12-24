#version 330 core
out vec4 FragColor;

in vec2 ourTexCoords;
in vec3 ourNormal;

// uniform sampler2D texture_diffuse1;
struct Material {
	sampler2D diffuse;
	sampler2D specular;
};

uniform Material material;

void main() {
	FragColor = texture(material.diffuse, ourTexCoords);
}