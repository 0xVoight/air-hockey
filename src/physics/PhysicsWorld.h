#pragma once

#include "../world/World.h"
#include "../core/Input.h"

class PhysicsWorld {
public:
    PhysicsWorld();

    // фиксированный шаг симуляции
    void simulate(World& world, const InputState& input, double dt);

    void setFriction(float friction) { m_friction = friction; }
    void setRestitution(float restitution) { m_restitution = restitution; }

private:
    void moveObjects(World& world, double dt);
    void handleCollisions(World& world);
    void processPaddles(World& world, const InputState& input);

private:
    float m_friction        = 0.15f; // замедление по воздуху
    float m_restitution     = 0.95f; // упругость ударов
    float m_paddleSpeed     = 1.5f;
    float m_paddleInfluence = 0.5f;
    float m_maxPuckSpeed    = 2.5f;
};
