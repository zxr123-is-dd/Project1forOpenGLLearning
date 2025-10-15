#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, const int size) {
	glGenBuffers(1, &mID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}