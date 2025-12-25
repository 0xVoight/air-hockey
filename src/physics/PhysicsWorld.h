#pragma once

#include "../world/World.h"
#include "../core/Input.h"

class PhysicsWorld
{
public:
    PhysicsWorld();

    // фиксированный шаг симуляции
    void simulate(World& world, const InputState& input, double dt) const;

    void setFriction(const float friction) { m_friction = friction; }
    void setRestitution(const float restitution) { m_restitution = restitution; }

private:
    void moveObjects(World& world, double dt) const;
    void handleCollisions(World& world) const;
    void processPaddles(World& world, const InputState& input) const;

private:
    float m_friction = 0.15f; // замедление по воздуху
    float m_restitution = 0.95f; // упругость ударов
    float m_paddleSpeed = 1.5f;
    float m_paddleInfluence = 0.5f;
    float m_maxPuckSpeed = 2.5f;
};
