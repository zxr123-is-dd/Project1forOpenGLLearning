#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <concepts>
#include <type_traits>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template<typename T>
concept ValidUniformType = 
	std::is_same_v<T, bool> ||
	std::is_same_v<T, int> ||
	std::is_same_v<T, float> ||
	std::is_same_v<T, glm::mat4> ||
	std::is_same_v<T, glm::vec3>;

class Shader {
public:
	Shader(const std::string& vertPath, const std::string& fragPath);
	~Shader();

	void use() const;

	template<ValidUniformType T>
	void setUniform(const std::string& name, T val) const;

private:
	unsigned int mID;

	unsigned int loadShader(const std::string& path) const;
	std::string readFile(const std::string& path) const;
};