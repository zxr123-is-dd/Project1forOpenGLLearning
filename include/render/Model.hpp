#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Mesh {
    GLuint vao{ 0 };
    GLuint vbo{ 0 };
    GLuint ebo{ 0 };
    uint32_t indexCount{ 0 };
    uint32_t materialId{ 0 };
};

class Model {
public:
    Model(const std::string& name, std::vector<Mesh>&& meshes);
    ~Model();

    Model(const Model&) = delete;
    Model& operator=(const Model&) = delete;

    const std::vector<Mesh>& getMeshes() const;
    const std::string& getName() const;

private:
    std::string name_;
    std::vector<Mesh> meshes_;

    glm::vec3 minBounds_{ 0.0f };
    glm::vec3 maxBounds_{ 0.0f };
};