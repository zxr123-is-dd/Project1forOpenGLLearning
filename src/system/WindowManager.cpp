#include "system/WindowManager.hpp"

#include <iostream>
#include <functional>

WindowManager::WindowManager() : window(nullptr) {}

WindowManager::~WindowManager() {
    cleanUp();
}

bool WindowManager::init(int height, int width, const std::string& windowTitle) {
    this->height = height;
    this->width = width;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(height, width, windowTitle.c_str(), NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glViewport(0, 0, height, width);
    
    return true;
}

bool WindowManager::windowShouldClose() const {
    return glfwWindowShouldClose(window);
}

void WindowManager::swapBuffers() const {
    glfwSwapBuffers(window);
}

void WindowManager::pollEvents() const {
    glfwPollEvents();
}

void WindowManager::processInput() const {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void WindowManager::cleanUp() {
    if (window) {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void WindowManager::framebufferSizeCallback(GLFWwindow* window, int height, int width) {
    glViewport(0, 0, height, width);
}