#pragma once

#include <glad/glad.h>
#include <iostream>

#include "VertexAttrib.h"

class VertexBuffer {
private:
	unsigned int mID;

public:
	VertexBuffer(const float* data, const int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};