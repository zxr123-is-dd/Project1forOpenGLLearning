/*
 * author	: zxr123
 * version	: 0.02
 * date		: 2025/7/16
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexAttrib.h"
#include "IndexBuffer.h"

constexpr unsigned int screenWidth = 1280;
constexpr unsigned int screenHeight = 960;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastPosX = screenWidth >> 1;
float lastPosY = screenHeight >> 1;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
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
	if (yaw > 180.0f) {
		yaw -= 360.0f;
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

int main(int argc, char** argv) {
	if (!glfwInit()) {
		std::cout << "Failed to initialize glfw" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "project1", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	VertexArray VAO;
	VAO.Bind();

	VertexBuffer VBO(vertices, sizeof(vertices));

	VertexAttrib VAt;
	VAt.Add(0, GL_FLOAT, 3);
	VAt.Add(1, GL_FLOAT, 2);
	VAt.Add(2, GL_FLOAT, 3);
	VAt.SetAttrib();

	IndexBuffer IBO(indices, sizeof(indices));

	Shader shader("./res/shader/shader.vert", "./res/shader/shader.frag");
	shader.Enable();

	glActiveTexture(GL_TEXTURE0);
	Texture texture0("./res/texture/container.jpg", 3);
	shader.SetInt("Texture0", 0);
	
	glActiveTexture(GL_TEXTURE1);
	Texture texture1("./res/texture/awesomeface.png", 4);
	shader.SetInt("Texture1", 1);

	glActiveTexture(GL_TEXTURE2);
	Texture texture2("./res/texture/container2.png", 4);
	shader.SetInt("material.diffuse", 2);

	glActiveTexture(GL_TEXTURE3);
	Texture texture3("./res/texture/container2_specular.png", 4);
	shader.SetInt("material.specular", 3);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);

	shader.SetMat4("projection", projection);

	VAO.Unbind();
	shader.Disable();

	// light
	VertexArray lightVAO;
	lightVAO.Bind();

	VertexAttrib lightVertexAttrib;
	lightVertexAttrib.Add( 0, GL_FLOAT, 3);
	lightVertexAttrib.Add(-1, GL_FLOAT, 5);

	VBO.Bind();
	lightVertexAttrib.SetAttrib();

	Shader lightShader("./res/shader/lightshader.vert", "./res/shader/lightshader.frag");
	lightShader.Enable();

	glm::vec3 lightPos(5.0f, 3.0f, 0.0f);

	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));
	
	lightShader.SetMat4("model", lightModel);
	lightShader.SetMat4("projection", projection);
	lightShader.Disable();

	shader.Enable();

	// light
	shader.SetVec3("light.position", lightPos);
	// shader.SetVec3("light.direction", glm::vec3(1.0f, 1.0f, 1.0f));

	shader.SetVec3("light.color", glm::vec3(1.0f));
	shader.SetVec3("light.ambient", glm::vec3(0.05f));
	shader.SetVec3("light.diffuse", glm::vec3(0.7f));
	shader.SetVec3("light.specular", glm::vec3(1.2f));

	shader.SetFloat("light.constant", 1.0f);
	shader.SetFloat("light.linear", 0.09f);
	shader.SetFloat("light.quadratic", 0.032f);

	// material
	// shader.SetVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	// shader.SetVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	// shader.SetVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	shader.SetFloat("material.shininess", 32.0f);

	// flash light
	shader.SetVec3("flashLight.color", glm::vec3(1.0f));

	shader.Disable();

	float angle = 0.0f, r = 5.0f;

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		angle += 1.0;
		lightPos.x = cos(glm::radians(angle)) * r;
		lightPos.z = sin(glm::radians(angle)) * r;

		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		VAO.Bind();
		shader.Enable();
		shader.SetVec3("light.position", lightPos);
		shader.SetVec3("viewPos", cameraPos);

		shader.SetVec3("flashLight.position", cameraPos);
		shader.SetVec3("flashLight.direction", cameraFront);
		shader.SetFloat("flashLight.cutOff", glm::cos(glm::radians(12.5f)));

		for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::rotate(model, glm::radians(15.0f * i), glm::vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 place = glm::mat4(1.0f);
			place = glm::translate(place, cubePositions[i]);

			shader.SetMat4("place", place);
			shader.SetMat4("model", model);
			shader.SetMat4("view", view);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		shader.Disable();
		
		lightShader.Enable();
		lightShader.SetMat4("view", view);

		lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		lightShader.SetMat4("model", lightModel);

		lightVAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightShader.Disable();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}