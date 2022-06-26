#pragma once

class VertexBuffer {
private:
	unsigned int m_RendererID = 0;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	static void Unbind() ;
};