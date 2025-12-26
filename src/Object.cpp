#include "Object.h"

Object::Object(std::shared_ptr<Model> model, glm::vec3 position, glm::vec3 scale) 
    : model_(model), position_(position), scale_(scale) {}

Object::~Object() {}

void Object::draw(const Shader& shader, const Camera& camera) const {
    shader.use();

    shader.setUniform<glm::mat4>("projection", camera.getProjection());
    shader.setUniform<glm::mat4>("view", camera.getView());

    glm::mat4 place = glm::mat4(1.0f);
    place = glm::translate(place, position_);
    shader.setUniform<glm::mat4>("place", place);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, scale_);
    shader.setUniform<glm::mat4>("model", model);

    shader.setUniform<glm::vec3>("viewPos", camera.getPosition());

    model_->draw(shader);
}