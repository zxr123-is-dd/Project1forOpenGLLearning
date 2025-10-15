#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const float* data, const int size) {
	glGenBuffers(1, &mID);
	glBindBuffer(GL_ARRAY_BUFFER, mID);
	
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {

}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, mID);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}