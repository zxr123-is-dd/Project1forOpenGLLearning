#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include "Shader.h"
#include "Model.h"
#include "Window.h"

constexpr unsigned int screenWidth = 1920;
constexpr unsigned int screenHeight = 1080;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

// void processInput(GLFWwindow* window) {
// 	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
// 		glfwSetWindowShouldClose(window, true);
// 	}

// 	float cameraSpeed = 2.5f * deltaTime;
// 	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
// 		cameraPos += glm::normalize(glm::cross(cameraUp, glm::cross(cameraFront, cameraUp))) * cameraSpeed;
// 	}
// 	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
// 		cameraPos -= glm::normalize(glm::cross(cameraUp, glm::cross(cameraFront, cameraUp))) * cameraSpeed;
// 	}
// 	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
// 		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
// 	}
// 	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
// 		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
// 	}
// 	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
// 		cameraPos += cameraUp * cameraSpeed;
// 	}
// 	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
// 		cameraPos -= cameraUp * cameraSpeed;
// 	}
// }

int main(int argc, char** argv) {
	Window window(screenWidth, screenHeight, "demo 0.03");

	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), -90.0f, 0.0f, screenWeight, screenHeight);

	Shader shader("res/shaders/shader1.vert", "res/shaders/shader1.frag");

	Model ourModel("res/models/backpack/backpack.obj");

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// std::cout << 1.0f / deltaTime << std::endl;
		// std::cout << "Pos: (" << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << ")\n";
		// std::cout << "Front: (" << cameraFront.x << ", " << cameraFront.y << ", " << cameraFront.z << ")" << std::endl;

		// processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.setMat4("projection", camera.getProjection());
		shader.setMat4("view", camera.getView());

		glm::mat4 model = glm::mat4(1.0f);
		// model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.setMat4("model", model);

		ourModel.draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}