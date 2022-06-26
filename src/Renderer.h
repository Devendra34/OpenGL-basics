#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <csignal>

#define ASSERT(x) if (!(x)) raise(SIGTRAP)
#define GLCall(x) GLClearError();\
	x;\
	GLLogCall(#x, __FILE__, __LINE__)

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


class Renderer {
public:
	static void Clear() ;
	static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) ;
};