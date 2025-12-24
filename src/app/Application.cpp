#include "Application.h"

#include "platform/IWindow.h"
#include "platform/GlfwWindow.h"

#include "core/Game.h"
#include "core/Time.h"

#include "render/IRenderer.h"
#include "render/OpenGLRenderer.h"

Application::Application() = default;
Application::~Application() = default;

int Application::run()
{
    init();
    loop();
    shutdown();
    return 0;
}

void Application::init()
{
    m_window = std::make_unique<GlfwWindow>(1280, 720, "Air Hockey");
    m_renderer = std::make_unique<OpenGLRenderer>(*m_window);
    m_game = std::make_unique<Game>();

    m_running = true;
}

void Application::loop()
{
    Time time;

    while (m_running && !m_window->shouldClose()) {
        time.update();
        m_window->pollEvents();

        m_game->physics().applyPlayerInput(m_game->world(), m_window->input(), time.delta());

        m_game->update(time.delta());

        m_renderer->beginFrame();
        m_renderer->render(m_game->world());
        m_renderer->endFrame();

        m_window->swapBuffers();
    }
}

void Application::shutdown()
{

}
