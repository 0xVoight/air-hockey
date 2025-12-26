#include "Game.h"
#include <iostream>

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
    m_world.leftGoal = {
        m_world.rink.left,
        -0.25f,
        0.25f,
        GoalSide::Left
    };

    m_world.rightGoal = {
        m_world.rink.right,
        -0.25f,
        0.25f,
        GoalSide::Right
    };
    m_world.goalScoredThisStep = false;
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
    m_physics.simulate(m_world, input, fixedDt, m_events);

    for (const GameEvent& event : m_events.consume())
    {
        handleEvent(event);
    }
    std::cout << "\r" << "Match score: " << m_match.leftScore() << " : " << m_match.rightScore() << std::flush;
}

void Game::handleEvent(const GameEvent& event)
{
    switch (event.type)
    {
    case GameEventType::Goal:
        {
            const auto& goal = std::get<GoalEvent>(event.payload);
            m_match.onGoal(goal.side);

            if (m_match.status() == MatchStatus::Finished)
            {
                m_events.push(
                    GameEvent::makeMatchFinished(*m_match.winner())
                );
            }
            else
            {
                m_events.push(GameEvent::makeRoundReset());
            }
            break;
        }

    case GameEventType::RoundReset:
        reset();
        break;

    case GameEventType::MatchReset:
        //resetMatch();
        break;

    case GameEventType::MatchFinished:
        m_events.push(GameEvent::makeMatchReset());
        break;
    }
}
