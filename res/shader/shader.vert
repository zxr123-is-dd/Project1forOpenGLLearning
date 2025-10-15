#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 ourTexCoord;
out vec3 ourNormal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 place;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * place * model * vec4(aPos, 1.0f);
	ourTexCoord = aTexCoord;
	ourNormal = vec3(model * vec4(aNormal, 1.0f));
	FragPos = vec3(place * model * vec4(aPos, 1.0f));
}
