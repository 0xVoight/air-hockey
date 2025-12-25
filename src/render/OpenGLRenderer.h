#pragma once

#include <memory>
#include <vector>

#include "math/Math.h"
#include "IRenderer.h"
#include "platform/IWindow.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "world/World.h"

class OpenGLRenderer final : public IRenderer {
public:
    explicit OpenGLRenderer(const IWindow& window);
    ~OpenGLRenderer() override;

    void beginFrame() override;
    void render(const World& world) override;
    void endFrame() override;

private:
    void setupResources();
    void drawCircle(const glm::vec2& position, float radius, const glm::vec3& color);
    void updateProjection();
    glm::vec2 worldToScreen(const glm::vec2& worldPos) const;

private:
    const IWindow& m_window;

    // todo: resource manager
    // лед
    std::unique_ptr<Shader> m_iceShader;
    std::unique_ptr<VertexArray> m_iceVAO;
    std::unique_ptr<Texture> m_iceTexture;
    uint32_t m_iceVBO = 0;

    // Круги
    std::unique_ptr<Shader> m_circleShader;
    std::unique_ptr<VertexArray> m_circleVAO;
    uint32_t m_circleVBO = 0;
    uint32_t m_circleVertexCount = 0;

    // Линии поля
    std::unique_ptr<Shader> m_lineShader;
    std::unique_ptr<VertexArray> m_rinkLinesVAO;
    uint32_t m_rinkLinesVBO = 0;
    uint32_t m_rinkLinesVertexCount = 0;

    float m_goalLineRadius = 0.05f;

    glm::mat4 m_projection = glm::mat4(1.0f);

    Rink m_worldRink;
};
