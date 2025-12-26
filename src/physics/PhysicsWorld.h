#pragma once

#include "../world/World.h"
#include "../core/Input.h"
#include "core/GameEvent.h"

class PhysicsWorld
{
public:
    PhysicsWorld();

    // фиксированный шаг симуляции
    void simulate(World& world, const InputState& input, double dt, GameEventQueue& events) const;

    void setFriction(const float friction) { m_friction = friction; }
    void setRestitution(const float restitution) { m_restitution = restitution; }

private:
    void moveObjects(World& world, double dt) const;
    void handleCollisions(World& world) const;
    void processPaddles(World& world, const InputState& input) const;
    [[nodiscard]] bool checkGoal(const World& world, const Goal& goal) const;

private:
    float m_friction = 0.15f; // замедление по воздуху
    float m_restitution = 0.96f; // упругость ударов
    float m_paddleSpeed = 1.8f;
    float m_paddleInfluence = 0.6f;
    float m_maxPuckSpeed = 2.8f;
};
