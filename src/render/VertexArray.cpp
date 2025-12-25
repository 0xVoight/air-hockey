#include "VertexArray.h"

// Специализации шаблона для разных типов данных
template <>
void VertexBufferLayout::push<float>(const uint32_t count)
{
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArray::bind() const
{
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const uint32_t vbo, const VertexBufferLayout& layout) const
{
    bind();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    const auto& elements = layout.getElements();
    uint64_t offset = 0;

    for (uint32_t i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            element.count,
            element.type,
            element.normalized,
            layout.getStride(),
            reinterpret_cast<const void*>(offset)
        );

        offset += static_cast<uint64_t>(element.count) * VertexBufferElement::getSizeOfType(element.type);
    }
}
