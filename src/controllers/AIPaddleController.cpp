#include "AIPaddleController.h"
#include <glm/glm.hpp>

AIPaddleController::AIPaddleController(const float reactionSpeed)
    : m_reactionSpeed(reactionSpeed)
{
}

void AIPaddleController::update(InputState& input,
                                const World& world)
{
    auto& ai = input.player2;
    ai = {};

    const auto& paddle = world.rightPaddle;
    const auto& puck = world.puck;

    m_mode = (puck.velocity.x > 0.0f)
                 ? Mode::Defend
                 : Mode::Attack;

    if (m_mode == Mode::Defend)
    {
        m_targetX = world.rink.right - m_defendXOffset;
        m_targetY = predictPuckY(world, m_targetX);
    }
    else
    {
        m_targetX = puck.position.x - m_attackXOffset;
        m_targetY = puck.position.y;
    }

    m_targetX = glm::clamp(
        m_targetX,
        0.0f,
        world.rink.right - paddle.radius
    );

    m_targetY = glm::clamp(
        m_targetY,
        world.rink.bottom + paddle.radius,
        world.rink.top - paddle.radius
    );

    const glm::vec2 delta{
        m_targetX - paddle.position.x,
        m_targetY - paddle.position.y
    };

    if (std::abs(delta.x) > m_deadZone)
        (delta.x > 0.0f) ? ai.right = true : ai.left = true;

    if (std::abs(delta.y) > m_deadZone)
        (delta.y > 0.0f) ? ai.up = true : ai.down = true;
}

float AIPaddleController::predictPuckY(const World& world, const float targetX)
{
    const auto& puck = world.puck;

    if (std::abs(puck.velocity.x) < 0.0001f)
        return puck.position.y;

    const float t = (targetX - puck.position.x) / puck.velocity.x;
    if (t < 0.0f)
        return puck.position.y;

    return puck.position.y + puck.velocity.y * t;
}
