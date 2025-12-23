#include "Camera.h"

Camera::Camera(glm::vec3 position, float yaw, float pitch, float width, float height, float fov, float farPlane)
	: position_(position), yaw_(yaw), pitch_(pitch), width_(width), height_(height), projection_(glm::mat4(1.0f)) {

	up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	calcDirection();
	calcView();
	setProjection(fov, farPlane);
}

Camera::~Camera() {

}

void Camera::moveDirection(float yaw, float pitch) {
	yaw_ += yaw;
	while (yaw_ > 360.0f) {
		yaw_ -= 360.0f;
	}
	while (yaw < -360.0f) {
		yaw_ += 360.0f;
	}

	pitch_ += pitch;
	if (pitch_ > 89.5f) {
		pitch_ = 89.5f;
	}
	if (pitch_ < -89.5f) {
		pitch_ = -89.5f;
	}
	
	calcDirection();
	calcView();
}

void Camera::setDirection(float yaw, float pitch) {
	yaw_ = yaw;
	while (yaw_ > 360.0f) {
		yaw_ -= 360.0f;
	}
	while (yaw_ < -360.0f) {
		yaw_ += 360.0f;
	}

	pitch_ = pitch;
	if (pitch_ > 89.5f) {
		pitch_ = 89.5f;
	}
	if (pitch_ < -89.5f) {
		pitch_ = -89.5f;
	}

	calcDirection();
	calcView();
}

void Camera::movePosition(glm::vec3 pos) {
	position_ += pos;
	calcView();
}

void Camera::setPosition(glm::vec3 pos) {
	position_ = pos;
	calcView();
}

void Camera::setProjection(float fov, float farPlane) {
	projection_ = glm::perspective(glm::radians(fov), width_ / height_, 0.1f, farPlane);
}

glm::vec3 Camera::getPosition() const {
	return position_;
}

glm::vec3 Camera::getFront() const {
	return front_;
}

glm::vec3 Camera::getUp() const {
	return up_;
}

const glm::mat4& Camera::getProjection() const {
	return projection_;
}

const glm::mat4& Camera::getView() const {
	return view_;
}

// private

void Camera::calcDirection() {
	front_.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
	front_.y = sin(glm::radians(pitch_));
	front_.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
	front_ = glm::normalize(front_);
}

void Camera::calcView() {
	view_ = glm::lookAt(position_, position_ + front_, up_);
}