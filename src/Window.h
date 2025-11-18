#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Camera.h"

class Window {
public:
	Window(const int &screenWidth, const int &screenHeight, const std::string &windowName);
	~Window();

	void process();

private:
	void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	// window
	GLFWwindow *window;
	float screenWidth;
	float screenHeight;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Cursor
	float posX;
	float posY;
	bool firstMouse = true;
};