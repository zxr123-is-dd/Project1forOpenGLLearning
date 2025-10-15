#pragma once

#include <glad/glad.h>

#include <iostream>
#include <vector>
#include <cstdint>

struct DataStruct {
	int location;
	unsigned int type;
	int cnt;
};

class VertexAttrib {
private:
	std::vector<DataStruct> mAttrib;
	int mSize;

	int Size(unsigned int type) const;

public:
	VertexAttrib();
	~VertexAttrib();

	void Add(const int location, const unsigned int type, const int cnt);
	void SetAttrib() const;
};