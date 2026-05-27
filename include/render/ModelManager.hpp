#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <fx/gltf.h>
#include <glm/glm.hpp>

#include "render/Model.hpp"

using ModelId = uint32_t;
constexpr ModelId INVALID_MODEL_ID = 0xFFFFFFFF;

class ModelManager {
public:
    ModelManager();
    ~ModelManager();

    ModelId loadModelGLB(const std::string& modelPath);
    
private:
    std::unordered_map<ModelId, std::unique_ptr<Model>> modelRegister_;
    std::unordered_map<std::string, ModelId> pathCache_;
    ModelId nextId = 0;
    
    std::vector<Mesh> parseMeshes(const fx::gltf::Document& doc, const std::vector<std::vector<uint8_t>>& meshBuffers);
};