#pragma once

#include <vector>

#include "math/Math.h"
#include "IRenderer.h"
#include "platform/IWindow.h"

class OpenGLRenderer final : public IRenderer {
public:
    explicit OpenGLRenderer(const IWindow& window);
    ~OpenGLRenderer() override;

    void beginFrame() override;
    void render(const World& world) override;
    void endFrame() override;

    inline void drawCircle(float x, float y, float radius);

private:
    void precomputeCircleGeometry(int segments);

private:
    const IWindow& m_window;
    std::vector<Vec2> m_unitCircleVertices;
};
