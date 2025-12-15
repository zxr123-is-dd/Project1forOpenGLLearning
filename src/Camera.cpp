#include "Camera.h"

Camera::Camera(glm::vec3 pos, float yaw, float pitch, float width, float height, float fov, float farPlane) :
	pos(pos), yaw(yaw), pitch(pitch), width(width), height(height), projection(glm::mat4(1.0f)) {

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	calcDirect();
	calcView();
	setProjection(fov, farPlane);
}

Camera::~Camera() {

}

void Camera::moveDirect(float _yaw, float _pitch) {
	yaw += _yaw;
	while (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	while (yaw < -360.0f) {
		yaw += 360.0f;
	}

	pitch += _pitch;
	if (pitch > 89.5f) {
		pitch = 89.5f;
	}
	if (pitch < -89.5f) {
		pitch = -89.5f;
	}
	
	calcDirect();
}

void Camera::setDirect(float _yaw, float _pitch) {
	yaw = _yaw;
	while (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	while (yaw < -360.0f) {
		yaw += 360.0f;
	}

	pitch = _pitch;
	if (pitch > 89.5f) {
		pitch = 89.5f;
	}
	if (pitch < -89.5f) {
		pitch = -89.5f;
	}

	calcDirect();
}

void Camera::movePos(glm::vec3 _pos) {
	pos += _pos;
}

void Camera::setPos(glm::vec3 _pos) {
	pos = _pos;
}

void Camera::setProjection(float fov, float farPlane) {
	projection = glm::perspective(glm::radians(fov), width / height, 0.1f, farPlane);
}

glm::vec3 Camera::getPos() const {
	return pos;
}

glm::vec3 Camera::getFront() const {
	return front;
}

glm::vec3 Camera::getUp() const {
	return up;
}

const glm::mat4& Camera::getProjection() const {
	return projection;
}

const glm::mat4& Camera::getView() {
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
	view = glm::lookAt(pos, pos + front, up);
}