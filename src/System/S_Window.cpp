#include "System/S_Window.h"

#include <iostream>

S_Window::S_Window()
    : window_(NULL) {}

S_Window::~S_Window() {
    glfwTerminate();
}

bool S_Window::init(int width, int height, const std::string &title) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize glfw" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window_ == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
	
	glfwMakeContextCurrent(window_);
	glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);
	glfwSwapInterval(1);

    glfwSetWindowUserPointer(window_, cameraData_);
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window_, mouseCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad" << std::endl;
		return false;
	}
	glEnable(GL_DEPTH_TEST);

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    return true;
}

glm::vec2 S_Window::getMouseOffset() const {
    return glm::vec2(cameraData_->offsetX, cameraData_->offsetY);
}

bool S_Window::isRunning() const {
    return !glfwWindowShouldClose(window_);
}

void S_Window::processInput() {
}

void S_Window::clear() const {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void S_Window::output() const {
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow *window, double xPos, double yPos) {
	static bool firstMouse = true;
	static float lastPosX;
	static float lastPosY;

	if (firstMouse) {
		lastPosX = xPos;
		lastPosY = yPos;
		firstMouse = false;
	}

    CameraData *cam = (CameraData *)glfwGetWindowUserPointer(window);

	cam->offsetX = (xPos - lastPosX) * cam->sensitivity;
	cam->offsetY = (lastPosY - yPos) * cam->sensitivity;

	lastPosX = xPos;
	lastPosY = yPos;
}