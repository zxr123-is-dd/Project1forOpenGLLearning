#include "Window.h"

Window::Window(const int &screenWidth, const int &screenHeight, const std::string &windowName) :
screenWidth(screenWidth),
screenHeight(screenHeight) {
	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenWidth, screenHeight, "project1", NULL, NULL);
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


// private
void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastPosX = xpos;
		lastPosY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastPosX;
	float yoffset = lastPosY - ypos;
	lastPosX = xpos;
	lastPosY = ypos;

	constexpr float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	if (pitch > 89.9f) {
		pitch = 89.9f;
	}
	if (pitch < -89.9f) {
		pitch = -89.9f;
	}
 	if (yaw < -180.0f) {
		yaw += 360.0f;
	}
	
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}