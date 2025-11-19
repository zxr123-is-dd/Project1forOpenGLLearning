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
		const glm::vec3& pos,
		const float& yaw, const float& pitch,
		const float& width,	const float& height,
		const float& fov = 45.0f, const float& farPlane = 100.0f
	);
	~Camera();

	void moveDirect(const float& _yaw, const float& _pitch);
	void setDirect(const float& _yaw, const float& _yaw);
	void movePos(const glm::vec3& _pos);
	void setPos(const glm::vec3& _pos);
	void setProjection(const float& fov, const float& farPlane);

	const glm::mat4& getProjection() const;
	const glm::mat4& getView() const;

private:
	void calcDirect();

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;

	glm::mat4 projection;
	glm::mat4 view;

	float yaw;
	float pitch;

	float& width;
	float& height;
};