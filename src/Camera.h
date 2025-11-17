#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(const glm::vec3 &pos, const glm::vec3 &front, const glm::vec3 &up);
	~Camera();

private:
	std::shared_ptr<glm::vec3> pos;
	std::shared_ptr<glm::vec3> front;
	std::shared_ptr<glm::vec3> up;

	float yaw;
	float pitch;
	float roll;
};