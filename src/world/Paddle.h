#pragma once

#include "math/Math.h"

struct Paddle
{
    glm::vec2 position{0.0f, 0.0f};
    glm::vec2 velocity{0.0f, 0.0f};

    float radius = 0.077f;
};
