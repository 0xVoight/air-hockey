#pragma once

#include "../core/Time.h"
#include "platform/PlatformFactory.h"

#include <memory>

class IWindow;
class Game;
class IRenderer;

class Application
{
public:
    explicit Application(std::unique_ptr<PlatformFactory> factory);
    ~Application();

    int run();

private:
    void init();
    void loop();
    void shutdown();

private:
    bool m_running = false;
    bool m_isPaused = false;

    std::unique_ptr<IWindow> m_window;
    std::unique_ptr<Game> m_game;
    std::unique_ptr<IRenderer> m_renderer;

    std::unique_ptr<PlatformFactory> m_factory;

    Time m_time;
};
