#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class WindowManager {
public:
    WindowManager();
    ~WindowManager();

    WindowManager(const WindowManager&&) = delete;
    WindowManager& operator=(const WindowManager&) = delete;

    bool init(int height, int width, const std::string& windowTitle);
    bool windowShouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;
    void processInput() const;

private:
    GLFWwindow* window;
    int height;
    int width;

    inline static bool isGLFWInitalized = false;

    void cleanUp();

    static void framebufferSizeCallback(GLFWwindow* window, int height, int width);
};