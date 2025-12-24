#pragma once

#include "../world/World.h"
#include "../core/Input.h"

class PhysicsWorld {
public:
    PhysicsWorld();

    // фиксированный шаг симуляции
    void simulate(World& world, double dt);

    void setFriction(float friction) { m_friction = friction; }
    void setRestitution(float restitution) { m_restitution = restitution; }

    void applyPlayerInput(World& world, const InputState& input, double dt);
private:
    void moveObjects(World& world, double dt);
    void handleCollisions(World& world);
    void processPaddleMovement(Paddle& paddle, const PlayerInput& pInput, const Rink& rink, bool isLeft, float dt);

private:
    float m_friction    = 0.0f; // замедление по воздуху
    float m_restitution = 1.0f; // упругость ударов
};
