#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cstring>
#include <map>

#include <glad/glad.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#include "Mesh.h"
#include "Camera.h"

class Model {
public:
	Model(const std::string &path);
	~Model();

	void draw(const Shader &shader);

private:
	std::vector<StaticMesh> staticMeshes_;
	std::vector<CollisionMesh> collisionMeshes_;
	std::vector<Texture> texturesLoaded_;
	std::string directory_;
	bool gammaCorrection_;

	void loadModel(const std::string &path);
	void processNode(aiNode *node, const aiScene *scene);
	StaticMesh processStaticMesh(aiMesh *mesh, const aiScene *scene);
	CollisionMesh processCollisionMesh(aiMesh *mesh);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string &typeName);
};

static unsigned int textureFromFile(const char *path, const std::string &directory, bool gamma = false);