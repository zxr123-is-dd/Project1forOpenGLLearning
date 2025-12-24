#include "Shader.h"

// shader does not be used in this function
Shader::Shader(const std::string& vertPath, const std::string& fragPath)
: mID(0) {
	unsigned int vs = loadShader(vertPath);
	unsigned int fs = loadShader(fragPath);
	if (!vs || !fs) {
		if (vs) {
			glDeleteShader(vs);
		}
		if (fs) {
			glDeleteShader(fs);
		}
		exit(-1);
	}
	
	mID = glCreateProgram();
	glAttachShader(mID, vs);
	glAttachShader(mID, fs);
	glLinkProgram(mID);

	// check
	{
		int success;
		char InfoLog[512];
		glGetProgramiv(mID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(mID, 512, NULL, InfoLog);
			std::cout << "Failed to link the program\nError: " << InfoLog << std::endl;
			exit(-1);
		}
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader() {}

void Shader::use() const {
	glUseProgram(mID);
}

template<ValidUniformType T>
void Shader::setUniform(const std::string& name, T val) const {
}

template<>
void Shader::setUniform<bool>(const std::string& name, bool v) const {
	glUniform1i(glGetUniformLocation(mID, name.c_str()), v);
}

template<>
void Shader::setUniform<int>(const std::string& name, int v) const {
	glUniform1i(glGetUniformLocation(mID, name.c_str()), v);
}

template<>
void Shader::setUniform<float>(const std::string& name, float v) const {
	glUniform1f(glGetUniformLocation(mID, name.c_str()), v);
}

template<>
void Shader::setUniform<glm::mat4>(const std::string& name, glm::mat4 v) const {
	glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
}

template<>
void Shader::setUniform<glm::vec3>(const std::string& name, glm::vec3 v) const {
	glUniform3f(glGetUniformLocation(mID, name.c_str()), v.x, v.y, v.z);
}

unsigned int Shader::loadShader(const std::string& path) const {
	unsigned int type = 0;
	if (path.find(".vert") != std::string::npos) {
		type = GL_VERTEX_SHADER;
		std::cout << "Vertex shader" << std::endl;
	} else if (path.find(".frag") != std::string::npos) {
		type = GL_FRAGMENT_SHADER;
		std::cout << "fragment shader" << std::endl;
	}
	
	if (!type) {
		std::cout << "Failed to recoglize type of the file" << std::endl;
		return 0;
	}

	std::string ssource = readFile(path);
	const char* source = ssource.c_str();
	unsigned int shader = glCreateShader(type);
	if (!shader) {
		std::cout << "Failed to creat a shader" << std::endl;
		return 0;
	}

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	// check
	{
		int success;
		char infoLog[512];
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Failed to compile the shader\nError: " << infoLog << std::endl;
			return 0;
		}
	}

	std::cout << "Shader compile successfully, shader ID is " << shader << std::endl;

	return shader;
}

std::string Shader::readFile(const std::string& path) const {
	std::ifstream stream(path);
	if (!stream.is_open()) {
		std::cout << "Failed to	open file: " << path << std::endl;
		return std::string();
	}

	std::stringstream res;
	std::string line;
	while (getline(stream, line)) {
		res << line << '\n';
	}

	return res.str();
}
