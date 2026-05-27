#include "system/WindowManager.hpp"

#include <iostream>
#include "system/Logger.hpp"

WindowManager::WindowManager() {}

WindowManager::~WindowManager() {
    cleanUp();
}

bool WindowManager::init(int height, int width, const std::string& windowTitle) {
    height_ = height;
    width_  = width;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(height, width, windowTitle.c_str(), NULL, NULL);
    if (window_ == NULL) {
        Logger::error("Failed to create GLFW window");
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger::error("Failed to initialize GLAD");
        return false;
    }
    glViewport(0, 0, height, width);
    
    Logger::info("GLFW and GLAD are loaded successfully");
    return true;
}

bool WindowManager::windowShouldClose() const {
    return glfwWindowShouldClose(window_);
}

void WindowManager::swapBuffers() const {
    glfwSwapBuffers(window_);
}

void WindowManager::pollEvents() const {
    glfwPollEvents();
}

void WindowManager::processInput() const {
    if(glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window_, true);
    }
}

void WindowManager::cleanUp() {
    if (window_) {
        glfwDestroyWindow(window_);
    }
    glfwTerminate();
}

void WindowManager::framebufferSizeCallback(GLFWwindow* window, int height, int width) {
    glViewport(0, 0, height, width);
}