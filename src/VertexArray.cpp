#include "VertexArray.h"

// Vertex Array Object dose not be binded in this function
VertexArray::VertexArray() {
	glGenVertexArrays(1, &mID);
}

VertexArray::~VertexArray() {

}

void VertexArray::Bind() const {
	glBindVertexArray(mID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}