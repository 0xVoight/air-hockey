#pragma once

#include "math/Vec2.h"

struct Paddle {
    Vec2 position;
    Vec2 velocity;

    float radius = 0.06f;
};
