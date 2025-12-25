#include "OpenGLRenderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

OpenGLRenderer::OpenGLRenderer(const IWindow& window)
    : m_window(window)
{
    m_worldRink = Rink{};
    setupResources();
}

OpenGLRenderer::~OpenGLRenderer() {
    glDeleteBuffers(1, &m_circleVBO);
    glDeleteBuffers(1, &m_rinkLinesVBO);
    glDeleteBuffers(1, &m_iceVBO);
}

void OpenGLRenderer::setupResources() {
    m_circleShader = std::make_unique<Shader>("assets/shaders/gl_circle.vert", "assets/shaders/gl_circle.frag");

    const int segments = 64;
    std::vector<Vec2> circleVerts;
    circleVerts.push_back({0.f, 0.f});
    for (int i = 0; i <= segments; ++i) {
        float angle = i / float(segments) * 2.0f * glm::pi<float>();
        circleVerts.push_back({std::cos(angle), std::sin(angle)});
    }
    m_circleVertexCount = static_cast<uint32_t>(circleVerts.size());

    glGenBuffers(1, &m_circleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_circleVBO);
    glBufferData(GL_ARRAY_BUFFER, circleVerts.size() * sizeof(Vec2), circleVerts.data(), GL_STATIC_DRAW);

    m_circleVAO = std::make_unique<VertexArray>();
    VertexBufferLayout layout;
    layout.push<float>(2);
    m_circleVAO->addBuffer(m_circleVBO, layout);
    m_circleVAO->unbind();
    ///
    m_lineShader = std::make_unique<Shader>("assets/shaders/gl_line.vert", "assets/shaders/gl_line.frag");

    std::vector<Vec2> rinkLineVertices;
    // границы
    rinkLineVertices.push_back({m_worldRink.left, m_worldRink.bottom});
    rinkLineVertices.push_back({m_worldRink.right, m_worldRink.bottom});
    rinkLineVertices.push_back({m_worldRink.right, m_worldRink.top});
    rinkLineVertices.push_back({m_worldRink.left, m_worldRink.top});
    // центр
    rinkLineVertices.push_back({0.f, m_worldRink.bottom});
    rinkLineVertices.push_back({0.f, m_worldRink.top});
    // ворота
    float goalWidth = m_goalLineRadius;
    rinkLineVertices.push_back({m_worldRink.left, goalWidth});
    rinkLineVertices.push_back({m_worldRink.left, -goalWidth});
    rinkLineVertices.push_back({m_worldRink.right, goalWidth});
    rinkLineVertices.push_back({m_worldRink.right, -goalWidth});

    m_rinkLinesVertexCount = static_cast<uint32_t>(rinkLineVertices.size());

    glGenBuffers(1, &m_rinkLinesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_rinkLinesVBO);
    glBufferData(GL_ARRAY_BUFFER, rinkLineVertices.size() * sizeof(Vec2), rinkLineVertices.data(), GL_STATIC_DRAW);

    m_rinkLinesVAO = std::make_unique<VertexArray>();
    VertexBufferLayout lineLayout;
    lineLayout.push<float>(2);
    m_rinkLinesVAO->addBuffer(m_rinkLinesVBO, lineLayout);
    m_rinkLinesVAO->unbind();

    ///
    m_iceShader = std::make_unique<Shader>("assets/shaders/gl_ice.vert", "assets/shaders/gl_ice.frag");
    m_iceTexture = std::make_unique<Texture>("assets/textures/ice.png");


    glGenBuffers(1, &m_iceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_iceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, nullptr, GL_DYNAMIC_DRAW);

    m_iceVAO = std::make_unique<VertexArray>();
    VertexBufferLayout iceLayout;
    iceLayout.push<float>(2); // pos
    iceLayout.push<float>(2); // uv
    m_iceVAO->addBuffer(m_iceVBO, iceLayout);
    m_iceVAO->unbind();
}

void OpenGLRenderer::updateProjection() {
    float w = float(m_window.width());
    float h = float(m_window.height());

    m_projection = glm::ortho(0.0f, w, 0.0f, h, -1.0f, 1.0f);

    float iceVerts[] = {
        0.f, 0.f, 0.f, 0.f,       // левый нижний угол
        w,   0.f, 1.f, 0.f,       // правый нижний угол
        w,   h,   1.f, 1.f,       // правый верхний угол
        0.f, h,   0.f, 1.f        // левый верхний угол
    };

    glBindBuffer(GL_ARRAY_BUFFER, m_iceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(iceVerts), iceVerts, GL_DYNAMIC_DRAW);
}



glm::vec2 OpenGLRenderer::worldToScreen(const glm::vec2 &worldPos) const
{
    float w = float(m_window.width());
    float h = float(m_window.height());

    float x = (worldPos.x - m_worldRink.left) / m_worldRink.width() * w;
    float y = (worldPos.y - m_worldRink.bottom) / m_worldRink.height() * h;

    return glm::vec2(x, y);
}


void OpenGLRenderer::beginFrame()
{
    glViewport(0, 0, m_window.width(), m_window.height());
    glClearColor(0.05f, 0.05f, 0.07f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    updateProjection();
}

void OpenGLRenderer::render(const World& world) {
    //Лед
    m_iceShader->use();
    m_iceShader->setMat4("uProjection", m_projection);
    m_iceTexture->bind(0);
    m_iceVAO->bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    m_iceVAO->unbind();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Линии
    m_lineShader->use();
    m_lineShader->setMat4("uProjection", m_projection);
    m_lineShader->setVec3("uColor", {0.8f, 0.2f, 0.2f});

    float w = float(m_window.width());
    float h = float(m_window.height());

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(w / 2.0f, h / 2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(w / 2.0f, h / 2.0f, 1.0f));

    m_lineShader->setMat4("uModel", model);

    m_rinkLinesVAO->bind();
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glDrawArrays(GL_LINES, 4, 2);
    glDrawArrays(GL_LINES, 6, 2);
    glDrawArrays(GL_LINES, 8, 2);
    m_rinkLinesVAO->unbind();

    //Шайба
    m_circleShader->use();
    m_circleShader->setMat4("uProjection", m_projection);
    m_circleVAO->bind();

    drawCircle(world.puck.position, world.puck.radius, {0.0f, 0.0f, 0.0f});

    // Биты
    drawCircle(world.leftPaddle.position, world.leftPaddle.radius, {0.2f, 0.4f, 1.0f});
    drawCircle(world.rightPaddle.position, world.rightPaddle.radius, {1.0f, 0.3f, 0.3f});

    m_circleVAO->unbind();
    glDisable(GL_BLEND);
}

void OpenGLRenderer::drawCircle(const Vec2& worldPosition, float worldRadius, const glm::vec3& color) {
    glm::vec2 screenPos = worldToScreen(worldPosition);

    float w = float(m_window.width());
    float h = float(m_window.height());
    float scale = std::min(w / m_worldRink.width(), h / m_worldRink.height());
    float screenRadius = worldRadius * scale;

    m_circleShader->setVec2("uInstancePos", screenPos);
    m_circleShader->setFloat("uInstanceRadius", screenRadius);
    m_circleShader->setVec3("uColor", color);

    glDrawArrays(GL_TRIANGLE_FAN, 0, m_circleVertexCount);
}


void OpenGLRenderer::endFrame() {}
