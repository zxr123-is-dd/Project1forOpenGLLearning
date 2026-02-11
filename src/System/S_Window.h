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

class S_Window {
public:
    S_Window();
    ~S_Window();
    
    bool init(int width, int height, const std::string &title);
    bool isRunning() const;
    void processInput();
    void clear() const;
    void output() const;

    glm::vec2 getMouseOffset() const;
private:
    GLFWwindow *window_;
    CameraData *cameraData_;
    
};

void framebufferSizeCallback(GLFWwindow *window, int width, int height);
void mouseCallback(GLFWwindow *window, double xPos, double yPos);