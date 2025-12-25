#pragma once

#include <glad/glad.h>
#include "math/Math.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader final
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept : m_id(other.m_id) { other.m_id = 0; }

    Shader& operator=(Shader&& other) noexcept
    {
        if (this != &other)
        {
            glDeleteProgram(m_id);
            m_id = other.m_id;
            other.m_id = 0;
        }
        return *this;
    }

    void use() const;

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
    uint32_t m_id = 0;
    mutable std::unordered_map<std::string, int32_t> m_uniformLocationCache;

    int32_t getUniformLocation(const std::string& name) const;
    void checkCompileErrors(uint32_t shader, const std::string& type);
    std::string readFile(const std::string& path);
};
