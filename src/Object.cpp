#include "Object.h"

Object::Object(std::shared_ptr<Model> model, glm::vec3 pos) 
    : model_(model), pos_(pos) {
}

Object::~Object() {
    model_.reset();
}

void Object::draw(const Shader& shader, const Camera& camera) const {
    shader.use();

    shader.setMat4("projection", camera.proj());
    shader.setMat4("view", camera.view());

    glm::mat4 place = glm::mat4(1.0f);
    place = glm::translate(place, pos_);
    shader.setMat4("place", place);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1.0f));
    shader.setMat4("model", model);

    model_->draw(shader);
}