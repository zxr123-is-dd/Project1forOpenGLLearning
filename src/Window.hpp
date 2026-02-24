#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>

struct CameraData {
    float offsetX;
    float offsetY;
    float sensitivity;
};

class WindowSystem {
    GLFWwindow *window_;
    CameraData *cameraData_;
public:
    WindowSystem();
    ~WindowSystem();
    
    bool Init(int width, int height, const std::string &title);
    bool IsRunning() const;
    void ProcessInput();
    void Clear() const;
    void SwapBuffers() const;
    void PollEvents() const;

    glm::vec2 GetMouseOffset() const;
};

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void mouseCallback(GLFWwindow *window, double xPos, double yPos);