#include "Camera.h"

Camera::Camera(glm::vec3 pos, float yaw, float pitch, float width, float height, float fov, float farPlane)
	: pos_(pos), yaw_(yaw), pitch_(pitch), width_(width), height_(height), proj_(glm::mat4(1.0f)) {

	up_ = glm::vec3(0.0f, 1.0f, 0.0f);
	calcDirect();
	calcView();
	setProj(fov, farPlane);
}

Camera::~Camera() {

}

void Camera::moveDirect(float yaw, float pitch) {
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
	
	calcDirect();
	calcView();
}

void Camera::setDirect(float yaw, float pitch) {
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

	calcDirect();
	calcView();
}

void Camera::movePos(glm::vec3 pos) {
	pos_ += pos;
	calcView();
}

void Camera::setPos(glm::vec3 pos) {
	pos_ = pos;
	calcView();
}

void Camera::setProj(float fov, float farPlane) {
	proj_ = glm::perspective(glm::radians(fov), width_ / height_, 0.1f, farPlane);
}

glm::vec3 Camera::pos() const {
	return pos_;
}

glm::vec3 Camera::front() const {
	return front_;
}

glm::vec3 Camera::up() const {
	return up_;
}

const glm::mat4& Camera::proj() const {
	return proj_;
}

const glm::mat4& Camera::view() const {
	return view_;
}

// private

void Camera::calcDirect() {
	front_.x = cos(glm::radians(pitch_)) * cos(glm::radians(yaw_));
	front_.y = sin(glm::radians(pitch_));
	front_.z = cos(glm::radians(pitch_)) * sin(glm::radians(yaw_));
	front_ = glm::normalize(front_);
}

void Camera::calcView() {
	view_ = glm::lookAt(pos_, pos_ + front_, up_);
}