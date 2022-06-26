#pragma once

class IndexBuffer {
private:
	unsigned int m_RendererID = 0;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	static void Unbind() ;

	[[nodiscard]] inline unsigned int GetCount() const { return m_Count; }
};