#include "render/Model.hpp"

#include <iostream>
#include <system/Logger.hpp>

Model::Model(const std::string& name, std::vector<Mesh>&& meshes)
    : name_(std::move(name)), meshes_(std::move(meshes)) {}

Model::~Model() {
    for (const auto& mesh : meshes_) {
        if (mesh.vao != 0) {
            glDeleteVertexArrays(1, &mesh.vao);
        }
        if (mesh.vbo != 0) {
            glDeleteBuffers(1, &mesh.vbo);
        }
        if (mesh.ebo != 0) {
            glDeleteBuffers(1, &mesh.ebo);
        }
    }

    Logger::info("Model ", name_, " has been released");
}

const std::vector<Mesh>& Model::getMeshes() const {
    return meshes_;
}

const std::string& Model::getName() const {
    return name_;
}