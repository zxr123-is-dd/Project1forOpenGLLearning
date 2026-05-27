#include "system/WindowManager.hpp"
#include "system/Logger.hpp"
#include "render/ModelManager.hpp"

int main(int argc, char** argv) {
	WindowManager myWindow;
	if (!myWindow.init(800, 600, "Test 1")) {
		return -1;
	}

	Logger::addListener(consoleLogListener);

	ModelManager myModelManager;
	myModelManager.loadModelGLB("res/1.glb");

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