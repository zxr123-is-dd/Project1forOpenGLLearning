#version 330 core

out vec4 FragColor;

in vec2 ourTexCoords;
in vec3 ourNormal;
in vec3 FragPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	bool available;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	bool available;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutoff;
	float outerCutoff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

	bool available;
};

// #define NUM_MATERIAL 16
#define NUM_DIRECT_LIGHT 4
#define NUM_POINT_LIGHT 16
#define NUM_SPOT_LIGHT 16

// uniform
uniform Material material;
uniform DirectLight directLights[NUM_DIRECT_LIGHT];
uniform PointLight pointLights[NUM_POINT_LIGHT];
uniform SpotLight spotLights[NUM_SPOT_LIGHT];

uniform vec3 viewPos;
// *******

vec3 CalcDirectLight(DirectLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(1.0f);
	vec3 diffuse = light.diffuse * diff * vec3(1.0f);
	vec3 specular = light.specular * spec * vec3(1.0f);

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	vec3 ambient = light.ambient * vec3(1.0f);
	vec3 diffuse = light.diffuse * diff * vec3(1.0f);
	vec3 specular = light.specular * spec * vec3(1.0f);

	return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);

	float diff = max(dot(normal, lightDir), 0.0);

	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	vec3 ambient = light.ambient * vec3(1.0f);
	vec3 diffuse = light.diffuse * diff * vec3(1.0f);
	vec3 specular = light.specular * spec * vec3(1.0f);

	return (ambient + diffuse + specular) * intensity * attenuation;
}

void main() {
	vec3 result = vec3(0.0);
	vec3 norm = normalize(ourNormal);
	vec3 viewDir = normalize(viewPos - FragPos);

	for (int i = 0; i < NUM_DIRECT_LIGHT; i++) {
		if (directLights[i].available) {
			result += CalcDirectLight(directLights[i], norm, viewDir);
		}
	}

	for (int i = 0; i < NUM_POINT_LIGHT; i++) {
		if (pointLights[i].available) {
			result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
		}
	}

	for (int i = 0; i < NUM_SPOT_LIGHT; i++) {
		if (spotLights[i].available) {
			result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);
		}
	}

	FragColor = vec4(result, 1.0);
}