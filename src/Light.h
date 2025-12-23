#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <type_traits>
#include <concepts>

#include <glm/glm.hpp>

#include "Shader.h"

enum LightStatus {
    On,
    Off,
    Blinking
};

enum LightType {
    Direct,
    Point,
    Spot
};

class BaseLight {
public:
    BaseLight(const std::string& name, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, LightType type);
    ~BaseLight() = default;
    virtual void setShader(const Shader& shader, int index) const = 0;
    void setStatus(LightStatus status);
    LightStatus getStatus() const;
    void setBrightness(float brightness);

protected:
    std::string name_;
    unsigned int id_;
    glm::vec3 ambient_;
	glm::vec3 diffuse_;
	glm::vec3 specular_;
    LightStatus status_;
    float brightness_;
    LightType type_;

private:
    static unsigned int totalLightCount_;
};

class DirectLight : public BaseLight {
public:
    DirectLight(const std::string& name, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
    ~DirectLight();
    void setShader(const Shader& shader, int index) const;

private:
    glm::vec3 direction_;
};

class PointLight : public BaseLight {
public:
    PointLight(const std::string& name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
    ~PointLight();
    void setShader(const Shader& shader, int index) const;

private:
    glm::vec3 position_;
	float constant_;
	float linear_;
	float quadratic_;
};

class SpotLight : public BaseLight {
public:
    SpotLight(const std::string& name, glm::vec3 position, glm::vec3 direction, float cutoff, float outerCutoff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic);
    ~SpotLight();
    void setShader(const Shader& shader, int index) const;

private:
    glm::vec3 position_;
    glm::vec3 direction_;
    float cutoff_;
    float outerCutoff_;
	float constant_;
	float linear_;
	float quadratic_;
};

constexpr unsigned int MAX_DIRECT_LIGHT_COUNT = 4;
constexpr unsigned int MAX_POINT_LIGHT_COUNT = 16;
constexpr unsigned int MAX_SPOT_LIGHT_COUNT = 16;

template<typename T>
concept ValidLightType =
    std::is_same_v<T, DirectLight> ||
    std::is_same_v<T, PointLight> ||
    std::is_same_v<T, SpotLight>;

class Lights {
public:
    Lights();
    ~Lights();

    template<ValidLightType T>
    void push(const T& light);

    void setShader(const Shader& shader) const;

private:
    template<ValidLightType T>
    void setLightOff(const Shader& shader, int index) const;

    std::vector<std::shared_ptr<DirectLight>> directLights_;
    std::vector<std::shared_ptr<PointLight>> pointLights_;
    std::vector<std::shared_ptr<SpotLight>> spotLights_;
};
