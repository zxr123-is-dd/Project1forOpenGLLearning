#pragma once

#include <vector>
#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Model.h"
#include "Shader.h"

class Camera {
public:
	Camera(
		const glm::vec3 &pos,
		const float &yaw,
		const float &pitch,
		const float &width,
		const float &height,
		const float &nearPlane = 0.1f,
		const float &farPlane = 100.0f,
		const float &fov = 45.0f
	);
	~Camera();

	void moveDirect(const float &_yaw, const float &_pitch);
	void movePos(const glm::vec3 &_pos);

	void drawWithoutLights(const std::vector<Model> &models, const std::string &shader) const;

private:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;

	float fov;
	glm::vec3 projection;

	float yaw;
	float pitch;
};