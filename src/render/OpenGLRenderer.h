#pragma once

#include "IRenderer.h"
#include "platform/IWindow.h"

class OpenGLRenderer final : public IRenderer {
public:
    explicit OpenGLRenderer(const IWindow& window);
    ~OpenGLRenderer() override;

    void beginFrame() override;
    void render(const World& world) override;
    void endFrame() override;

    static inline void drawCircle(float x, float y, float radius, int segments = 32);

private:
    const IWindow& m_window;
};
