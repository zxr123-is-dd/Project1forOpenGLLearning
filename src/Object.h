#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Model.h"
#include "Camera.h"

class Object {
public:
    Object(std::shared_ptr<Model> model, glm::vec3 pos, glm::vec3 scale = glm::vec3(1.0f));
    ~Object();

    void draw(const Shader& shader, const Camera& camera) const;

private:
    std::shared_ptr<Model> model_;
    glm::vec3 position_;
    glm::vec3 scale_;
};
