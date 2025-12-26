#pragma once

#include <random>

#include "GameEvent.h"
#include "world/World.h"
#include "physics/PhysicsWorld.h"

class Game
{
public:
    Game();

    void update(double dt, const InputState& input);
    void reset();

    // Чтение
    [[nodiscard]] const World& world() const { return m_world; }

    // Модификация
    World& world() { return m_world; }
    PhysicsWorld& physics() { return m_physics; }

private:
    void fixedUpdate(double fixedDt, const InputState& input);
    void handleEvent(const GameEvent& event);

private:
    World m_world;
    PhysicsWorld m_physics;
    double m_accumulator = 0.0;

    GameEventQueue m_events;
    MatchState m_match;

    std::mt19937 m_rng;

    static constexpr double FIXED_DT = 1.0 / 120.0;
};
