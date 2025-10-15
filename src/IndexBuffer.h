#pragma once

#include <glad/glad.h>

class IndexBuffer {
private:
	unsigned int mID;

public:
	IndexBuffer(const unsigned int* data, const int size);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
};