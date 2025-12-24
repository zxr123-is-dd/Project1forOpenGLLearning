#include "Object.h"

Object::Object(std::shared_ptr<Model> model, glm::vec3 pos) 
    : model_(model), pos_(pos) {
}

Object::~Object() {
    model_.reset();
}

void Object::draw(const Shader& shader, const Camera& camera) const {
    shader.use();

    shader.setUniform<glm::mat4>("projection", camera.getProjection());
    shader.setUniform<glm::mat4>("view", camera.getView());

    glm::mat4 place = glm::mat4(1.0f);
    place = glm::translate(place, pos_);
    shader.setUniform<glm::mat4>("place", place);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1.0f));
    shader.setUniform<glm::mat4>("model", model);

    model_->draw(shader);
}