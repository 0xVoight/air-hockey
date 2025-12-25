#pragma once

#include "../core/Input.h"

class IWindow
{
public:
    virtual ~IWindow() = default;

    virtual void pollEvents() = 0;
    virtual void swapBuffers() = 0;

    [[nodiscard]] virtual bool shouldClose() const = 0;

    [[nodiscard]] virtual int width() const = 0;
    [[nodiscard]] virtual int height() const = 0;

    [[nodiscard]] const InputState& input() const { return m_input; }

protected:
    InputState m_input;
};
