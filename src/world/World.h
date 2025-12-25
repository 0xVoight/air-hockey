#pragma once

#include "Puck.h"
#include "Paddle.h"
#include "Rink.h"

struct World
{
    Puck puck;
    Paddle leftPaddle;
    Paddle rightPaddle;
    Rink rink;
};
