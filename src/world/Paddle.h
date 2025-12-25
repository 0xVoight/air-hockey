#pragma once

#include "math/Math.h"

struct Paddle {
    Vec2 position{0.0f, 0.0f};
    Vec2 velocity{0.0f, 0.0f};

    float radius = 0.077f;
};
