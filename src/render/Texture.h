#pragma once
#include <string>
#include <glad/glad.h>

class Texture
{
public:
    explicit Texture(const std::string& path);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void unbind() const;

private:
    uint32_t m_id{};
};
