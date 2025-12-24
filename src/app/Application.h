#pragma once

#include <memory>

class IWindow;
class Game;
class IRenderer;

class Application {
public:
    Application();
    ~Application();

    int run();

private:
    void init();
    void loop();
    void shutdown();

private:
    bool m_running = false;

    std::unique_ptr<IWindow>   m_window;
    std::unique_ptr<Game>     m_game;
    std::unique_ptr<IRenderer> m_renderer;
};
