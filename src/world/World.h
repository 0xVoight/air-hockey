#pragma once

#include "Puck.h"
#include "Paddle.h"
#include "Rink.h"

enum class GoalSide;

struct Goal
{
    float x;
    float yMin;
    float yMax;

    GoalSide side;
};

struct World
{
    Puck puck;
    Paddle leftPaddle;
    Paddle rightPaddle;
    Goal leftGoal;
    Goal rightGoal;
    Rink rink;

    bool goalScoredThisStep = false;
};