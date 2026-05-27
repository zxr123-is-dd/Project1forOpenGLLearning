#include "render/ModelManager.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include "system/Logger.hpp"

namespace fs = std::filesystem;

ModelManager::ModelManager() {}

ModelManager::~ModelManager() {}

ModelId ModelManager::loadModelGLB(const std::string& modelPath) {
    if (pathCache_.find(modelPath) != pathCache_.end()) {
        Logger::error("This path of model has been loaded: ", modelPath);
        return pathCache_[modelPath];
    }

    Logger::info("The path of model is loding: ", modelPath);

    fs::path path(modelPath);

    if (!fs::exists(path)) {
        Logger::error("Can't find file: ", fs::absolute(path));
        return INVALID_MODEL_ID;
    }

    if (!fs::is_regular_file(path)) {
        Logger::error("The file is not a regular file (Maybe it's a folder, but not a valid file): ", fs::absolute(path));
        return INVALID_MODEL_ID;
    }

    std::string ext = path.extension().string();
    if (ext != ".glb") {
        Logger::error("This engine only support .glb file. This file is not valid: ", fs::absolute(path));
    }

    std::ifstream file(modelPath, std::ios::binary);
    if (file.is_open()) {
        uint32_t magic = 0;
        file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
        if (magic != 0x46546C67) {
            Logger::error("The internal signature (Magic) does not match, the file is corrupted! The file path: ", fs::absolute(path));
            return INVALID_MODEL_ID;
        }
    }

    try {
        fx::gltf::Document doc = fx::gltf::LoadFromBinary(modelPath);
        Logger::info("The model is successfully read: ", modelPath);
        
        std::vector<std::vector<uint8_t>> meshBuffers;
        for (const auto& buffer : doc.buffers) {
            meshBuffers.push_back(buffer.data);
        }

        auto uploadedMesh = parseMeshes(doc, meshBuffers);
        ModelId newId = nextId++;

        modelRegister_[newId] = std::make_unique<Model>(path.filename().string(), std::move(uploadedMesh));
        pathCache_[modelPath] = newId;

        return newId;
    } catch(const std::exception& e) {
        Logger::error("fx-gltf failed to parse deep data. The file path: ", fs::absolute(path));
        return INVALID_MODEL_ID;
    }
}

std::vector<Mesh> ModelManager::parseMeshes(const fx::gltf::Document& doc, const std::vector<std::vector<uint8_t>>& meshBuffers) {
    std::vector<Mesh> meshes;
    for (const auto& gltfMesh : doc.meshes) {
        for (const auto& primitive : gltfMesh.primitives) {
            Mesh myMesh;

            glGenVertexArrays(1, &myMesh.vao);
            glBindVertexArray(myMesh.vao);

            int posAccessorIdx = primitive.attributes.at("POSITION");
            const auto& posAccessor = doc.accessors[posAccessorIdx];
            const auto& posView = doc.bufferViews[posAccessor.bufferView];

            glGenBuffers(1, &myMesh.vbo);
            glBindBuffer(GL_ARRAY_BUFFER, myMesh.vbo);

            const uint8_t* posDataPtr = &meshBuffers[posView.buffer][posView.byteOffset + posAccessor.byteOffset];
            
            glBufferData(GL_ARRAY_BUFFER, posView.byteLength, posDataPtr, GL_STATIC_DRAW);
            
            GLsizei stride = posView.byteStride == 0 ? 3 * sizeof(float) : posView.byteStride;
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(0);

            if (primitive.indices >= 0) {
                const auto& idxAccessor = doc.accessors[primitive.indices];
                const auto& idxView = doc.bufferViews[idxAccessor.bufferView];

                glGenBuffers(1, &myMesh.ebo);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myMesh.ebo);

                const uint8_t* idxDataPtr = &meshBuffers[idxView.buffer][idxView.byteOffset + idxAccessor.byteOffset];
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, idxView.byteLength, idxDataPtr, GL_STATIC_DRAW);

                myMesh.indexCount = idxAccessor.count;
            }

            meshes.push_back(myMesh);
        }
    }
    return meshes;
}