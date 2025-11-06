#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, const int size) {
	glGenBuffers(1, &mID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
	std::cout << "IndexBuffer created and binded, ID: " << mID << std::endl;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &mID);
	std::cout << "IndexBuffer delete, ID: " << mID << std::endl;
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}