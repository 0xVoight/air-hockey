#pragma once

#include "IPlayerController.h"

class AIPaddleController final : public IPlayerController
{
public:
    explicit AIPaddleController(float reactionSpeed = 3.0f);

    void update(InputState& input,
                const World& world) override;

private:
    static float predictPuckY(const World& world, float targetX);

private:
    enum class Mode
    {
        Defend,
        Attack
    };

    Mode  m_mode = Mode::Defend;
    float m_reactionSpeed;
    float m_deadZone = 0.03f;

    float m_targetY = 0.0f;
    float m_targetX = 0.0f;

    float m_defendXOffset = 0.33f;
    float m_attackXOffset = 0.55f;
};
