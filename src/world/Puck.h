#pragma once

#include "math/Vec2.h"

struct Puck {
    Vec2 position;
    Vec2 velocity;

    float radius = 0.03f;
};
