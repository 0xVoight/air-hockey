#pragma once

#include "PlatformFactory.h"
#include "GlfwWindow.h"
#include "../render/OpenGLRenderer.h"

class DesktopFactory final : public PlatformFactory
{
public:
    std::unique_ptr<IWindow> createWindow(int w, int h, const char* title) override
    {
        return std::make_unique<GlfwWindow>(w, h, title);
    }

    std::unique_ptr<IRenderer> createRenderer(const IWindow& window) override
    {
        return std::make_unique<OpenGLRenderer>(window);
    }
};
