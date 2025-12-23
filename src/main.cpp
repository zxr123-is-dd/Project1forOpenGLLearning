#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Object.h"
#include "Light.h"

constexpr unsigned int screenWidth = 1920;
constexpr unsigned int screenHeight = 1080;

glm::vec2 mouseOffset = glm::vec2(0.0f);
float mouseSensitivity = 1.25f;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void processInput(GLFWwindow* window, Camera& camera);

int main(int argc, char** argv) {
	// Initalization
	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Demo 0.3", NULL, NULL);
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
	glfwSetCursorPosCallback(window, mouseCallback);

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// 
	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), -90.0f, 0.0f, screenWidth, screenHeight, 45.0f, 100.0f);
	Shader shader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
	std::shared_ptr<Model> ourModel = std::make_shared<Model>("../res/models/backpack/backpack.obj");

	PointLight pointLight();

	Object ourObject(ourModel, glm::vec3(0.0f));
	
	while (!glfwWindowShouldClose(window)) {
		// Input
		processInput(window, camera);

		camera.moveDirection(mouseOffset.x / 10.0f, mouseOffset.y / 10.0f);
		mouseOffset = glm::vec2(0.0f, 0.0f);

		// Draw
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourObject.draw(shader, camera);

	    glfwSwapBuffers(window);
	    glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xPos, double yPos) {
	static bool firstMouse = true;
	static float lastPosX;
	static float lastPosY;

	if (firstMouse) {
		lastPosX = xPos;
		lastPosY = yPos;
		firstMouse = false;
	}

	mouseOffset.x = (xPos - lastPosX) * mouseSensitivity;
	mouseOffset.y = (lastPosY - yPos) * mouseSensitivity;

	lastPosX = xPos;
	lastPosY = yPos;
}

void processInput(GLFWwindow* window, Camera& camera) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	glm::vec3 posOffset(0.0f, 0.0f, 0.0f);
	constexpr float cameraSpeed = 0.04f;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		posOffset += glm::normalize(glm::cross(camera.getUp(), glm::cross(camera.getFront(), camera.getUp()))) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		posOffset -= glm::normalize(glm::cross(camera.getUp(), glm::cross(camera.getFront(), camera.getUp()))) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		posOffset -= glm::normalize(glm::cross(camera.getFront(), camera.getUp())) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		posOffset += glm::normalize(glm::cross(camera.getFront(), camera.getUp())) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		posOffset += camera.getUp() * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		posOffset -= camera.getUp() * cameraSpeed;
	}

	camera.movePosition(posOffset);
}