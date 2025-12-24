#pragma once

#include "IWindow.h"

struct GLFWwindow;

class GlfwWindow final : public IWindow {
public:
    GlfwWindow(int width, int height, const char* title);
    ~GlfwWindow() override;

    void pollEvents() override;
    void swapBuffers() override;

    bool shouldClose() const override;

    int width() const override;
    int height() const override;

private:
    GLFWwindow* m_handle = nullptr;
};
