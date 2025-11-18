#include "Camera.h"

Camera::Camera(
	const glm::vec3 &pos,
	const float &yaw,
	const float &pitch,
	const float &width,
	const float &height,
	const float &nearPlane = 0.1f,
	const float &farPlane = 100.0f,
	const float &fov = 45.0f) :
pos(pos), front(front), up(up), fov(fov), projection(glm::mat4(1.0f)) {
	projection = glm::perspective(glm::radians(fov), width / height, nearPlane, farPlane);
}

Camera::~Camera() {

}

void Camera::changeDirect(const float &_yaw, const float &_pitch) {
	yaw += _yaw;
	pitch += _pitch;

	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

	front = glm::normalize(front);
}

void Camera::movePos(const glm::vec3 &_pos) {
	pos = pos + _pos;
}

void Camera::drawWithoutLights(const Model *models, const unsigned int &modelNum, const std::string &shader) {
	shader.use();

	shader.setMat4("projection", projection);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(pos, pos + front, up);
	shader.setMat4("view", view);

	glm::mat4 model = glm::mat4(1.0f);
	shader.setMat4("model", model);

	for (unsigned int i = 0; i < modelNum; i++) {
		if (models[i] == nullptr) {
			std::cout << "Null pointer to Model object" << std::endl;
			continue;
		}

		models->draw(shader);
	}
}