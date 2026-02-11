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

class StaticMesh {
public:
	StaticMesh(std::vector<Vertex> &&vertices, std::vector<unsigned int> &&indices, std::vector<Texture> &&textures);
	~StaticMesh();

	void draw(const Shader &shader) const;
	void print() const;

private:
	std::vector<Vertex> vertices_;
	std::vector<unsigned int> indices_;
	std::vector<Texture> textures_;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	
	void setup();
};

class CollisionMesh {
public:
	CollisionMesh(std::vector<glm::vec3> &&vertices, std::vector<unsigned int> &&indices);
	~CollisionMesh();

private:
	std::vector<glm::vec3> vertices_;
	std::vector<unsigned int> indices_;
};