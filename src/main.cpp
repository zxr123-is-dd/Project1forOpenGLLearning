#include "system/WindowManager.hpp"

int main(int argc, char** argv) {
	WindowManager myWindow;
	if (!myWindow.init(800, 600, "Test 1")) {
		return -1;
	}

	while (!myWindow.windowShouldClose()) {
		myWindow.processInput();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		myWindow.swapBuffers();
		myWindow.pollEvents();
	}

	glfwTerminate();
	return 0;
}