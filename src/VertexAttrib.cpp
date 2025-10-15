#include "VertexAttrib.h"

VertexAttrib::VertexAttrib() 
	: mSize(0) {

}

VertexAttrib::~VertexAttrib() {

}

void VertexAttrib::Add(const int location, const unsigned int type, const int cnt) {
	mAttrib.push_back({ location, type, cnt });
	mSize += Size(type) * cnt;
}

void VertexAttrib::SetAttrib() const {
	intptr_t ASize = 0;
	for (int i = 0; i < mAttrib.size(); i++) {
		if (mAttrib[i].location >= 0) {
			glVertexAttribPointer(mAttrib[i].location, mAttrib[i].cnt, mAttrib[i].type, GL_FALSE, mSize, (const void*)ASize);
			glEnableVertexAttribArray(i);
		}
		ASize += Size(mAttrib[i].type) * mAttrib[i].cnt;
	}
}

int VertexAttrib::Size(const unsigned int type) const {
	switch (type) {
	case GL_FLOAT:        return sizeof(float);
	case GL_INT:          return sizeof(int);
	case GL_UNSIGNED_INT: return sizeof(unsigned int);
	case GL_BYTE:         return sizeof(char);
	}
	std::cout << "Unknown type is queried!" << std::endl;
	return 0;
}