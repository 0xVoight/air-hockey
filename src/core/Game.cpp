#include "Game.h"

Game::Game() : m_rng(std::random_device{}())
{
    m_physics.setFriction(0.1f);
    m_physics.setRestitution(0.8f);

    reset();
}

void Game::update(const double dt, const InputState& input)
{
    m_accumulator += dt;

    while (m_accumulator >= FIXED_DT)
    {
        fixedUpdate(FIXED_DT, input);
        m_accumulator -= FIXED_DT;
    }
}

void Game::reset()
{
    m_world.puck.position = {0.f, 0.f};

    std::uniform_real_distribution<float> angleDist(0.0f, glm::two_pi<float>());
    std::uniform_real_distribution<float> speedDist(0.4f, 0.7f);

    const float randomAngle = angleDist(m_rng);
    const float randomSpeed = speedDist(m_rng);

    m_world.puck.velocity = glm::vec2(std::cos(randomAngle), std::sin(randomAngle)) * randomSpeed;

    m_world.leftPaddle.position = {-0.8f, 0.f};
    m_world.leftPaddle.velocity = {0.f, 0.f};

    m_world.rightPaddle.position = {0.8f, 0.f};
    m_world.rightPaddle.velocity = {0.f, 0.f};
}

void Game::fixedUpdate(const double fixedDt, const InputState& input)
{
    m_physics.simulate(m_world, input, fixedDt);
}
