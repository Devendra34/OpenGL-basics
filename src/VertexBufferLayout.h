#pragma once

#include <vector>
#include "Renderer.h"
#include "glad/glad.h"

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeofType(unsigned int type) {
        switch (type) {
            case GL_FLOAT:
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
            default:
                ASSERT(false);
                return 0;
        }
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout() : m_Stride(0) {}

    template<typename T>
    void Push(unsigned int count) {
        if constexpr (std::is_same_v<T, float>) {
            m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
            m_Stride += VertexBufferElement::GetSizeofType(GL_FLOAT) * count;
        } else if constexpr (std::is_same_v<T, unsigned int>) {
            m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            m_Stride += VertexBufferElement::GetSizeofType(GL_UNSIGNED_INT) * count;
        } else if constexpr (std::is_same_v<T, unsigned char>) {
            m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            m_Stride += VertexBufferElement::GetSizeofType(GL_UNSIGNED_BYTE) * count;
        }
        //static_assert(false);
    }

//	template<>
//	void Push<float>(unsigned int count) {
//		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
//		m_Stride += VertexBufferElement::GetSizeofType(GL_FLOAT) * count;
//	}
//
//	template<>
//	void Push<unsigned int>(unsigned int count) {
//		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
//		m_Stride += VertexBufferElement::GetSizeofType(GL_UNSIGNED_INT) * count;
//	}
//
//	template<>
//	void Push<unsigned char>(unsigned int count) {
//		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
//		m_Stride += VertexBufferElement::GetSizeofType(GL_UNSIGNED_BYTE) * count;
//	}

    [[nodiscard]] inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

    [[nodiscard]] inline unsigned int GetStride() const { return m_Stride; }
};