#include "Mesh.h"

//
// StaticMesh
//

StaticMesh::StaticMesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, std::vector<Texture>&& textures)
	: vertices_(std::move(vertices)), indices_(std::move(indices)), textures_(std::move(textures)) {
	setup();
	print();
}

StaticMesh::~StaticMesh() {
	// std::cout << "Delete Mesh" << std::endl;
}

void StaticMesh::draw(const Shader &shader) const {
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (unsigned int i = 0; i < textures_.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures_[i].type;

		if (name == "texture_diffuse") {
			number = std::to_string(diffuseNr++);
			shader.setUniform<int>("material.diffuse", i);
		} else if (name == "texture_specular") {
			number = std::to_string(specularNr++);
			shader.setUniform<int>("material.specular", i);
		}

		glBindTexture(GL_TEXTURE_2D, textures_[i].id);
	}
	glActiveTexture(GL_TEXTURE0);
	shader.setUniform<float>("material.shininess", 32.0f);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void StaticMesh::print() const {
	std::cout << "Length of vertices: " << vertices_.size() << "\n";
	std::cout << "Length of indices: " << indices_.size() << "\n";
	std::cout << "Lenght of textures: " << textures_.size() << "\n";
	std::cout << "VAO: " << VAO << " VBO: " << VBO << " EBO: " << EBO << std::endl;
	for (auto vertex : vertices_) {
		std::cout << vertex.Position.x << " " << vertex.Position.y << " " << vertex.Position.z << "\n";
	}
}

void StaticMesh::setup() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), vertices_.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

//
// CollisionMesh
//

CollisionMesh::CollisionMesh(std::vector<glm::vec3>&& vertices, std::vector<unsigned int>&& indices)
	: vertices_(std::move(vertices_)), indices_(std::move(indices)) {}

CollisionMesh::~CollisionMesh() {}