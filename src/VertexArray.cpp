#include "VertexArray.h"

// Vertex Array Object dose not be binded in this function
VertexArray::VertexArray() {
	glGenVertexArrays(1, &mID);
	std::cout << "VertexArray Created, ID: " << mID << std::endl;
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &mID);
	std::cout << "VertexArray Deleted, ID: " << mID << std::endl;
}

void VertexArray::Bind() const {
	glBindVertexArray(mID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}