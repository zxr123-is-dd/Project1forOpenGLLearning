#include "Camera.h"

Camera::Camera(
	const glm::vec3& pos,
	const float& yaw, const float& pitch,
	const float& width, const float& height,
	const float& fov = 45.0f, const float& farPlane = 100.0f) :
	pos(pos), front(front), up(up), projection(glm::mat4(1.0f)) {

	calcDirect();
	calcView();
	setProjection(fov, farPlane);
}

Camera::~Camera() {

}

void Camera::moveDirect(const float& _yaw, const float& _pitch) {
	yaw += _yaw;
	pitch += _pitch;
	calcDirect();
}

void Camera::setDirect(const float& _yaw, const float& _pitch) {
	yaw = _yaw;
	pitch = _pitch;
	calcDirect();
}

void Camera::movePos(const glm::vec3& _pos) {
	pos += _pos;
}

void Camera::setPos(const glm::vec3& _pos) {
	pos = _pos;
}

void Camera::setProjection(const float& fov, const float& farPlane) {
	projection = glm::perspective(glm::radians(fov), width / height, 0.1f, farPlane);
}

const glm::mat4& Camera::getProjection() const {
	return projection;
}

const glm::mat4& Camera::getView() const {
	calcView();
	return view;
}

// private

void Camera::calcDirect() {
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front = glm::normalize(front);
}

void Camera::calcView() {
	view = glm::LootAt(pos, pos + front, up);
}