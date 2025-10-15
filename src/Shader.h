/*
 * author	: zxr123
 * date		: 2025/7/14
 */
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
	private:
		unsigned int mID;

	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		~Shader();

		void Enable() const;
		void Disable() const;

		void SetBool(const std::string& name, bool v) const;
		void SetInt(const std::string& name, int v) const;
		void SetFloat(const std::string& name, float v) const;
		void SetMat4(const std::string& name, glm::mat4 v) const;
		void SetVec3(const std::string& name, glm::vec3 v) const;

	private:
		unsigned int LoadShader(const std::string& path) const;
		std::string ReadFile(const std::string& path) const;
};
