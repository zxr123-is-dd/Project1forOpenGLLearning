#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Model.h"
#include "Camera.h"
#include "Physics.h"

class BaseObject {
public:
    
};

class Object {
public:
    Object(std::shared_ptr<Model> model, glm::vec3 pos, glm::vec3 scale = glm::vec3(1.0f));
    ~Object();

    void draw(const Shader& shader, const Camera& camera) const;

protected:
    std::shared_ptr<Model> model_;
    glm::vec3 position_;
    glm::vec3 scale_;
};



// class Humanoid : public Object {
// public:
//     Humanoid(std::shared_ptr<Model> model, glm::vec3 pos, glm::vec3 scale = glm::vec3(1.0f), const Capsule &capsule);
//     ~Humanoid();

//     void checkIntersects(const std::vector<Object> &objects);

// private:
//     Capsule capsule_;
//     glm::vec3 speed_;
//     bool isGravity_;
// };