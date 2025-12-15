#pragma once

#include <vector>
#include <string>
#include <memory>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"
#include "Shader.h"

class Camera {
public:
	Camera(glm::vec3 pos, float yaw, float pitch, float width, float height, float fov, float farPlane);
	~Camera();

	void moveDirect(float _yaw, float _pitch);
	void setDirect(float _yaw, float _pitch);
	void movePos(glm::vec3 _pos);
	void setPos(glm::vec3 _pos);
	void setProjection(float fov, float farPlane);

	glm::vec3 getPos() const;
	glm::vec3 getFront() const;
	glm::vec3 getUp() const;

	const glm::mat4& getProjection() const;
	const glm::mat4& getView();

private:
	void calcDirect();
	void calcView();

	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up;

	glm::mat4 projection;
	glm::mat4 view;

	float yaw;
	float pitch;

	float width;
	float height;
};