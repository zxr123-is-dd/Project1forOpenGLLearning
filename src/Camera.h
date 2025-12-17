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
	void setProj(float fov, float farPlane);

	glm::vec3 pos() const;
	glm::vec3 front() const;
	glm::vec3 up() const;
	const glm::mat4& proj() const;
	const glm::mat4& view() const;

private:
	void calcDirect();
	void calcView();

	glm::vec3 pos_;
	glm::vec3 front_;
	glm::vec3 up_;

	glm::mat4 proj_;
	glm::mat4 view_;

	float yaw_;
	float pitch_;

	float width_;
	float height_;
};