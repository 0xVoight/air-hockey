#pragma once

class World;

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void beginFrame() = 0;
    virtual void render(const World& world) = 0;
    virtual void endFrame() = 0;
};
