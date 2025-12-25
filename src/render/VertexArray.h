#pragma once

#include <glad/glad.h>
#include <vector>
#include <cstdint>

struct VertexBufferElement
{
    uint32_t type;
    uint32_t count;
    uint8_t normalized;

    static uint32_t getSizeOfType(const uint32_t type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE: return 1;
        default: ;
        }
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() : m_stride(0)
    {
    }

    template <typename T>
    void push(uint32_t count);

    [[nodiscard]] inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }
    [[nodiscard]] inline uint32_t getStride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;
    uint32_t m_stride;
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addBuffer(uint32_t vbo, const VertexBufferLayout& layout) const;

private:
    uint32_t m_id{};
};
