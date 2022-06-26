#include "Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>

#include <iostream>

#include "Renderer.h"


Shader::Shader(const std::string &filePath) {
    auto shaderSource = ParseShader(filePath);
    m_RendererID = CreateShader(shaderSource.vertexSource, shaderSource.fragmentSource);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string &filePath) {

    std::fstream stream(filePath);
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };
    std::string line;
    auto shaderType = ShaderType::NONE;
    std::stringstream ss[2];
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                shaderType = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                shaderType = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int) shaderType] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

unsigned int Shader::CompileShader(const unsigned int &type, const std::string &source) {
    GLCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *) alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        auto typeStr = type == GL_VERTEX_SHADER ? "Vertex " : "Fragment";
        std::cout << "Failed to compile " << typeStr << "Shader\n";
        std::cout << message << std::endl;
    }

    return id;
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() {
    GLCall(glUseProgram(0));

}

void Shader::setUniform1i(const std::string &name, int value) {
    int location = GetUniformLocation(name);
    GLCall(glUniform1i(location, value));
}

[[maybe_unused]] void Shader::setUniform1f(const std::string &name, float value) {
    int location = GetUniformLocation(name);
    GLCall(glUniform1f(location, value));
}

void Shader::setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    int location = GetUniformLocation(name);
    GLCall(glUniform4f(location, v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    m_UniformLocationCache[name] = location;
    return location;
}