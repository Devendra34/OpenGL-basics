#include "Renderer.h"
#include "glad/glad.h"
#include <iostream>

void GLClearError() {
 	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    auto error = glGetError();
    if (error == 0) return true;
//	auto errorString =  glewGetErrorString(error);

    std::cout << "[OpenGL Error] (" << error << "): " << error<< " at :" << function << " " << file << ":" << line << std::endl;
    return false;
}

void Renderer::Clear() {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) {
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}