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

	void moveDirection(float _yaw, float _pitch);
	void setDirection(float _yaw, float _pitch);
	void movePosition(glm::vec3 _pos);
	void setPosition(glm::vec3 _pos);
	void setProjection(float fov, float farPlane);

	glm::vec3 getPosition() const;
	glm::vec3 getFront() const;
	glm::vec3 getUp() const;
	const glm::mat4& getProjection() const;
	const glm::mat4& getView() const;

private:
	void calcDirection();
	void calcView();

	glm::vec3 position_;
	glm::vec3 front_;
	glm::vec3 up_;

	glm::mat4 projection_;
	glm::mat4 view_;

	float yaw_;
	float pitch_;

	float width_;
	float height_;
};