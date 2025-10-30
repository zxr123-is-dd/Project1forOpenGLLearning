#version 330 core

out vec4 FragColor;

in vec3 ourLightColor;
in vec2 ourTexCoord;
in vec3 ourNormal;
in vec3 FragPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float     shininess;
};

struct Light {
	vec3 position;
	// vec3 direction;

	vec3 color;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct FlashLight {
	vec3 color;
	vec3 position;
	vec3 direction;
	float cutOff;
};

uniform Material material;
uniform Light light;
uniform FlashLight flashLight;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

uniform vec3 viewPos;

void main() {
	// ambient
	vec3 ambient = light.color * light.ambient * vec3(texture(material.diffuse, ourTexCoord));

	// diffuse
	vec3 norm = normalize(ourNormal);
	vec3 lightDir = normalize(light.position - FragPos);
	// vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * light.diffuse * diff * vec3(texture(material.diffuse, ourTexCoord));
	
	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.color * light.specular * spec * vec3(texture(material.specular, ourTexCoord));

	// attenuation
	float distance = length(lightDir);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	// flash light
	vec3 flashLightDir = normalize(flashLight.position - FragPos);
	float theta = dot(flashLightDir, normalize(-flashLight.direction));
	if (theta > flashLight.cutOff) {
		// Flash light diffuse
		diffuse = diffuse + flashLight.color * light.diffuse * vec3(texture(material.diffuse, ourTexCoord));

		// Flash light specular
		float fSpec = pow(max(dot(norm, flashLightDir), 0.0), material.shininess);
		specular = specular + flashLight.color * light.specular * fSpec * vec3(texture(material.specular, ourTexCoord));
	}

	vec3 result = (ambient + diffuse + specular) * attenuation;
	// FragColor = mix(texture(Texture0, ourTexCoord), texture(Texture1, ourTexCoord), 0.5) * vec4(result, 1.0f);
	FragColor = vec4(result, 1.0);
}