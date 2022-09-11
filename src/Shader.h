#pragma once

#include <string>
#include <unordered_map>
#include <glm.hpp>

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
private:
	unsigned int m_RendererID = 0;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	explicit Shader(const std::string& filePath);
	~Shader();

	void Bind() const;
	static void Unbind() ;

	void setUniform1i(const std::string& name, int value);

    [[maybe_unused]] void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void setUniformMat4f(const std::string& name, const glm::mat4 &matrix);
private:
	static ShaderProgramSource ParseShader(const std::string& filePath);
	static unsigned int CompileShader(const unsigned int &type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};

