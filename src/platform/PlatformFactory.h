#pragma once

#include <memory>
#include "IWindow.h"
#include "../render/IRenderer.h"

class PlatformFactory {
public:
    virtual ~PlatformFactory() = default;

    virtual std::unique_ptr<IWindow>  createWindow(int w, int h, const char* title) = 0;
    virtual std::unique_ptr<IRenderer> createRenderer(const IWindow& window) = 0;
};


/// todo: Separate the platform factory and the render factory
///       Enter WindowConfig / RendererConfig
///       Clarify the life cycle contract
