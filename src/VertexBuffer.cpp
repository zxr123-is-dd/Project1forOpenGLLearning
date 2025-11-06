#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float* data, const int size) {
	glGenBuffers(1, &mID);
	glBindBuffer(GL_ARRAY_BUFFER, mID);
	std::cout << "VertexBuffer created and binded, ID: " << mID << std::endl;
	
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &mID);
	std::cout << "VertexBuffer deleted, ID: " << mID << std::endl;
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}