#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.h>

#include "Camera.h"

class Window {
public:
	Window(const int &screenWidth, const int &screenHeight, const std::string &windowName);
	~Window();

	void process();
	const glm::vec2& getMouseOffset() const;
	const float& getDeltaTime() const;

private:
	void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	void input();
	void update();
	void draw();

	// window
	GLFWwindow *window;
	float screenWidth;
	float screenHeight;

	float deltaTime;
	float lastFrame;

	// Cursor
	float lastPosX;
	float lastPosY;

	glm::vec2 MouseOffset;

	float MouseSensitivity;
	bool isFirstMouse;
};