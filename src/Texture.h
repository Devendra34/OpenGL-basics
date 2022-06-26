#pragma once
#include <string>

class Texture {
private:
	unsigned int m_RendererID = 0;
    [[maybe_unused]] std::string m_FilePath;
	unsigned char* m_LocalBuffer = nullptr;
	int m_Width = 0, m_Height = 0, m_BPP = 0;
public:
    explicit Texture(const char *path);
    ~Texture();

	void Bind(unsigned int slot = 0) const;
	static void Unbind() ;

	[[maybe_unused]] [[nodiscard]] inline int GetWidth() const { return m_Width; }
	[[maybe_unused]] [[nodiscard]] inline int GetHeight() const { return m_Height; }
};

