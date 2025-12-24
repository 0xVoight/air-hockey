#pragma once

#include "world/World.h"
#include "physics/PhysicsWorld.h"

class Game {
public:
    Game();

    void update(double dt);

    // Чтение
    [[nodiscard]] const World& world() const { return m_world; }

    // Модификация
    World& world() { return m_world; }
    PhysicsWorld& physics() { return m_physics; }

private:
    void fixedUpdate(double fixedDt);

private:
    World m_world;
    PhysicsWorld m_physics;
    double m_accumulator = 0.0;

    static constexpr double FIXED_DT = 1.0 / 120.0;
};
