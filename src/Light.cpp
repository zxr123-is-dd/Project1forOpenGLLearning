#include "Light.h"

// class BaseLight

BaseLight::BaseLight(const std::string& name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, LightType type)
    : name_(name), id_(++totalLightCount_), ambient_(ambient), diffuse_(diffuse), specular_(specular), status_(LightStatus::On), brightness_(1.0f), type_(type) {}

void BaseLight::setStatus(LightStatus status) {
    status_ = status;
}

LightStatus BaseLight::getStatus() const {
    return status_;
}

void BaseLight::setBrightness(float brightness) {
    brightness_ = brightness;
}

unsigned int BaseLight::totalLightCount_ = 0;

// class DirectLight

DirectLight::DirectLight(const std::string& name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
: BaseLight(name, ambient, diffuse, specular, LightType::Direct), direction_(direction) {}

DirectLight::~DirectLight() {}

void DirectLight::setShader(const Shader& shader, int index) const {
    std::string number = std::to_string(index);
    shader.setVec3("directLights[" + number + "].direction", direction_);
    shader.setVec3("directLights[" + number + "].ambient", ambient_ * brightness_);
    shader.setVec3("directLights[" + number + "].diffuse", diffuse_ * brightness_);
    shader.setVec3("directLights[" + number + "].specular", specular_ * brightness_);
    shader.setBool("directLights[" + number + "].available", true);
}

// class PointLight

PointLight::PointLight(const std::string& name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
    : BaseLight(name, ambient, diffuse, specular, LightType::Point), position_(position), constant_(constant), linear_(linear), quadratic_(quadratic) {}

PointLight::~PointLight () {}

void PointLight::setShader(const Shader& shader, int index) const {
    std::string number = std::to_string(index);
    shader.setVec3("pointLights[" + number + "].position", position_);
    shader.setVec3("pointLights[" + number + "].ambient", ambient_ * brightness_);
    shader.setVec3("pointLights[" + number + "].diffuse", diffuse_ * brightness_);
    shader.setVec3("pointLights[" + number + "].specular", specular_ * brightness_);
    shader.setFloat("pointLights[" + number + "].constant", constant_);
    shader.setFloat("pointLights[" + number + "].linear", linear_);
    shader.setFloat("pointLights[" + number + "].quadratic", quadratic_);
    shader.setBool("pointLights[" + number + "].available", true);
}

// class SpotLight

SpotLight::SpotLight(const std::string& name, glm::vec3 position, glm::vec3 direction, float cutoff, float outerCutoff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
    : BaseLight(name, ambient, diffuse, specular, LightType::Spot), position_(position), direction_(direction), cutoff_(cutoff), outerCutoff_(outerCutoff), constant_(constant), linear_(linear), quadratic_(quadratic) {}

SpotLight::~SpotLight() {}

void SpotLight::setShader(const Shader& shader, int index) const {
    std::string number = std::to_string(index);
    shader.setVec3("spotLights[" + number + "].position", position_);
    shader.setVec3("spotLights[" + number + "].ambient", ambient_ * brightness_);
    shader.setVec3("spotLights[" + number + "].diffuse", diffuse_ * brightness_);
    shader.setVec3("spotLights[" + number + "].specular", specular_ * brightness_);
    shader.setFloat("spotLights[" + number + "].cutoff", cutoff_);
    shader.setFloat("spotLights[" + number + "].outerCutoff", outerCutoff_);
    shader.setFloat("spotLights[" + number + "].constant", constant_);
    shader.setFloat("spotLights[" + number + "].linear", linear_);
    shader.setFloat("spotLights[" + number + "].quadratic", quadratic_);
    shader.setBool("spotLights[" + number + "].available", true);
}

// class Lights

Lights::Lights() {}

Lights::~Lights() {}

template<ValidLightType T>
void Lights::push(const T& light) {
    std::cout << "The type is "
}

template<>
void Lights::push<DirectLight>(const DirectLight& light) {
    if (directLights_.size() < MAX_DIRECT_LIGHT_COUNT) {
        directLights_.push_back(std::make_shared<DirectLight>(light));
    } else {
        std::cout << "The maximum number of direct lights has been reached" << std::endl;
    }
}

template<>
void Lights::push<PointLight>(const PointLight& light) {
    if (pointLights_.size() < MAX_POINT_LIGHT_COUNT) {
        pointLights_.push_back(std::make_shared<PointLight>(light));
    } else {
        std::cout << "The maximum number of point lights has been reached" << std::endl;
    }
}

template<>
void Lights::push<SpotLight>(const SpotLight& light) {
    if (spotLights_.size() < MAX_SPOT_LIGHT_COUNT) {
        spotLights_.push_back(std::make_shared<SpotLight>(light));
    } else {
        std::cout << "The maximum number of spot lights has been reached" << std::endl;
    }
}

void Lights::setShader(const Shader& shader) const {
    for (unsigned int i = 0; i < directLights_.size(); i++) {
        switch (directLights_[i]->getStatus()) {
            case LightStatus::On: directLights_[i]->setShader(shader, i); break;
            case LightStatus::Off: setLightOff(shader, i); break;
            case LightStatus::Blinking: break;
        }
    }
    for (unsigned int i = directLights_.size(); i < MAX_DIRECT_LIGHT_COUNT; i++) {
        
    }
    
}

void Lights::setLightOff(const Shader& shader, int index) const {
    std::string number = std::to_string(index);
    
}