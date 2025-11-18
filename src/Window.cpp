#include "Window.h"

Window::Window(const int &screenWidth, const int &screenHeight, const std::string &windowName) :
screenWidth(screenWidth),
screenHeight(screenHeight),
lastFrame(glfwGetTime()),
deltaTime(0.0f),
firstMouse(true) {
	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

}

Window::~Window() {

}

void Window::process() {

}

const glm::vec2& Window::getMouseOffset() const {
	return mouseOffset;
}

const float& Window:getDeltaTime() const {
	return deltaTime;
}

// private
void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Window::mouse_callback(GLFWwindow* window, double xPos, double yPos) {
	if (firstMouse) {
		lastPosX = xPos;
		lastPosY = yPos;
		isFirstMouse = false;
	}

	mouseOffset.x = (xPos - lastPosX) * sensitivity;
	mouseOffset.y = (lastPosY - yPos) * sensitivity;

	lastPosX = xPos;
	lastPosY = yPos;
}

void Window::input() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraUp, glm::cross(cameraFront, cameraUp))) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraUp, glm::cross(cameraFront, cameraUp))) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		cameraPos += cameraUp * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		cameraPos -= cameraUp * cameraSpeed;
	}
}

void Window::update() {

}

void Window::draw() {

}