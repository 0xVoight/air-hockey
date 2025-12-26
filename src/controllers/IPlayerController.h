#pragma once

#include "core/Input.h"
#include "world/World.h"

class IPlayerController
{
public:
    virtual ~IPlayerController() = default;

    virtual void update(InputState& input,
                        const World& world) = 0;
};
