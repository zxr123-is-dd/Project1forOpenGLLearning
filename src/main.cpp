#include "Window.hpp"

#include <iostream>

constexpr unsigned int screenWidth = 1920;
constexpr unsigned int screenHeight = 1080;

int main(int argc, char **argv) {
	WindowSystem myWindow;
	if (!myWindow.Init(screenWidth, screenHeight, "Demo 0.4")) {
		std::cout << "Window failed to loaded" << std::endl;
		return -1;
	}

	std::cout << "This demo try to use ECS to organize the data." << std::endl;

	while (myWindow.IsRunning()) {
		// Process Input
		myWindow.ProcessInput();

		myWindow.Clear();
		// Draw

		myWindow.SwapBuffers();
		myWindow.PollEvents();
	}

	return 0;
}