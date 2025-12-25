#include "Application.h"

#include "platform/IWindow.h"
#include "render/IRenderer.h"

#include "core/Game.h"

Application::Application(std::unique_ptr<PlatformFactory> factory) : m_factory(std::move(factory))
{
}

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
    m_window = m_factory->createWindow(1280, 720, "Air Hockey");
    m_renderer = m_factory->createRenderer(*m_window);

    m_game = std::make_unique<Game>();
    m_running = true;
}

void Application::loop()
{
    m_time.update();

    while (m_running && !m_window->shouldClose())
    {
        m_time.update();

        m_window->pollEvents();

        if (!m_isPaused)
        {
            m_game->update(m_time.delta(), m_window->input());
        }

        m_renderer->beginFrame();
        m_renderer->render(m_game->world());
        m_renderer->endFrame();

        m_window->swapBuffers();
    }
}

void Application::shutdown()
{
}
