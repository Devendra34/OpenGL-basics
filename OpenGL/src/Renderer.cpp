#include "Renderer.h"
#include <iostream>

void GLClearError() {
 	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		auto errorString =  glewGetErrorString(error);
		std::cout << "[OpenGL Error] (" << error << "): " << errorString << " at :" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}