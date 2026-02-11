#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include "System/S_Window.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include "Physics.h"

constexpr unsigned int screenWidth = 1920;
constexpr unsigned int screenHeight = 1080;

glm::vec2 mouseOffset = glm::vec2(0.0f);
float mouseSensitivity = 1.25f;

int main(int argc, char **argv) {
	S_Window myWindow;
	if (!myWindow.init(screenWidth, screenHeight, "Demo 0.4")) {
		std::cout << "Window failed to loaded" << std::endl;
		return -1;
	}

	Camera camera(glm::vec3(0.0f, 0.0f, 5.0f), -90.0f, 0.0f, screenWidth, screenHeight, 45.0f, 500.0f);
	Shader shader("../res/shaders/shader.vert", "../res/shaders/shader.frag");
	// auto ourModel = std::make_shared<Model>("../res/models/backpack/backpack.obj");

	Shader shader1("../res/shaders/shader1.vert", "../res/shaders/shader1.frag");
	auto ourModel1 = std::make_shared<Model>("../res/models/test1/Scene1.fbx");

	// Object ourObject(ourModel, glm::vec3(5.0f, 0.0f, -3.0f));
	Object ourObject1(ourModel1, glm::vec3(0.0f, -3.0f, 0.0f));

	auto pointLight1 = std::make_shared<PointLight>("point light 1", glm::vec3(3.0f), glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.3f), 1.0f, 0.09f, 0.032f);
	auto directLight1 = std::make_shared<DirectLight>("direct light 1", glm::vec3(-1.0f, -2.0f, -3.0f), glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(0.3f));
	auto spotLight1 = std::make_shared<SpotLight>("spot light 1", glm::vec3(-2.0f, 7.0f, 0.0f), glm::vec3(1.0f, -1.0f, 0.0f), 30.0f, 45.0f, glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.3f), 1.0f, 0.09f, 0.032f);

	Lights lights1;
	lights1.push<PointLight>(pointLight1);
	lights1.push<DirectLight>(directLight1);
	lights1.push<SpotLight>(spotLight1);

	// pointLight1->setBrightness(3.0f);
	// spotLight1->setBrightness(3.0f);

	float angle = 0.0f;

	while (myWindow.isRunning()) {
		// Input
		myWindow.processInput();

		camera.moveDirection(mouseOffset.x / 10.0f, mouseOffset.y / 10.0f);
		mouseOffset = glm::vec2(0.0f, 0.0f);

		angle += 0.01f;
		spotLight1->setDirection(glm::vec3(glm::cos(angle), -1.0f, glm::sin(angle)));

		// Draw
		myWindow.clear();

		// lights1.setShader(shader);
		// ourObject.draw(shader, camera);

		lights1.setShader(shader1);
		ourObject1.draw(shader1, camera);

		myWindow.output();
	}

	return 0;
}