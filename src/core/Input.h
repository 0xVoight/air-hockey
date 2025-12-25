#pragma once

struct PlayerInput
{
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
};

struct InputState
{
    PlayerInput player1;
    PlayerInput player2;
};
