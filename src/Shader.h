#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	~Shader();

	void use() const;
	void setBool(const std::string& name, bool v) const;
	void setInt(const std::string& name, int v) const;
	void setFloat(const std::string& name, float v) const;
	void setMat4(const std::string& name, glm::mat4 v) const;
	void setVec3(const std::string& name, glm::vec3 v) const;

private:
	unsigned int mID;

	unsigned int loadShader(const std::string& path) const;
	std::string readFile(const std::string& path) const;
};