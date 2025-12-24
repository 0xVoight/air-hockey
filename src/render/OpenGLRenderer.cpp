#include "OpenGLRenderer.h"

#include "core/Game.h"

#include <GL/gl.h>

OpenGLRenderer::OpenGLRenderer(const Window& window)
    : m_window(window)
{
    glViewport(0, 0, m_window.width(), m_window.height());

    // Настройка 2D проекции в пикселях
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_window.width(), 0, m_window.height(), -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

OpenGLRenderer::~OpenGLRenderer() = default;

void OpenGLRenderer::beginFrame()
{
    int w = m_window.width();
    int h = m_window.height();

    glViewport(0, 0, w, h);

    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_window.width(), 0, m_window.height(), -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OpenGLRenderer::render(const World& world)
{
    int w = m_window.width();
    int h = m_window.height();

    float scaleX = 0.5f * w;
    float scaleY = 0.5f * h;
    float offsetX = w * 0.5f;
    float offsetY = h * 0.5f;
    float radiusScale = std::min(scaleX, scaleY);

    auto toPixelX = [scaleX, offsetX](float x){ return x * scaleX + offsetX; };
    auto toPixelY = [scaleY, offsetY](float y){ return y * scaleY + offsetY; };

    // Шайба
    glColor3f(1.f, 1.f, 1.f);
    drawCircle(toPixelX(world.puck.position.x),
               toPixelY(world.puck.position.y),
               world.puck.radius * radiusScale);

    // Левая бита
    glColor3f(0.f, 0.f, 1.f);
    drawCircle(toPixelX(world.leftPaddle.position.x),
               toPixelY(world.leftPaddle.position.y),
               world.leftPaddle.radius * radiusScale);

    // Правая бита
    glColor3f(1.f, 0.f, 0.f);
    drawCircle(toPixelX(world.rightPaddle.position.x),
               toPixelY(world.rightPaddle.position.y),
               world.rightPaddle.radius * radiusScale);

    // Ринк
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(toPixelX(world.rink.left),  toPixelY(world.rink.bottom));
    glVertex2f(toPixelX(world.rink.right), toPixelY(world.rink.bottom));
    glVertex2f(toPixelX(world.rink.right), toPixelY(world.rink.top));
    glVertex2f(toPixelX(world.rink.left),  toPixelY(world.rink.top));
    glEnd();
}

void OpenGLRenderer::endFrame()
{
}

void OpenGLRenderer::drawCircle(float x, float y, float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for(int i = 0; i <= segments; ++i) {
        float angle = i / (float)segments * 2.f * 3.1415926f;
        float vx = x + std::cos(angle) * radius;
        float vy = y + std::sin(angle) * radius;
        glVertex2f(vx, vy);
    }
    glEnd();
}
