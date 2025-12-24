#pragma once

#include "Renderer.h"
#include "platform/Window.h"

class OpenGLRenderer final : public Renderer {
public:
    explicit OpenGLRenderer(const Window& window);
    ~OpenGLRenderer() override;

    void beginFrame() override;
    void render(const World& world) override;
    void endFrame() override;

    static inline void drawCircle(float x, float y, float radius, int segments = 32);

private:
    const Window& m_window;
};
