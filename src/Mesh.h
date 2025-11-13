#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include <assimp/scene.h>
#include <glad/glad.h>

#include "Shader.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};

class Mesh {
public:
	Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, std::vector<Texture>&& textures);
	~Mesh();

	void draw(const Shader &shader);

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void setupMesh();
	void print();
};