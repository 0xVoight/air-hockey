#include "MatchState.h"

MatchState::MatchState() = default;

std::optional<GoalSide> MatchState::winner() const noexcept
{
    if (m_status != MatchStatus::Finished)
        return std::nullopt;

    return (m_leftScore > m_rightScore)
               ? std::optional<GoalSide>{GoalSide::Left}
               : std::optional<GoalSide>{GoalSide::Right};
}

void MatchState::setScoreLimit(const int limit) noexcept
{
    if (limit > 0)
        m_scoreLimit = limit;
}

void MatchState::onGoal(const GoalSide side)
{
    if (m_status == MatchStatus::Finished)
        return;

    if (side == GoalSide::Left)
        ++m_rightScore;
    else
        ++m_leftScore;

    checkForFinish();
}

void MatchState::checkForFinish() noexcept
{
    if (m_leftScore >= m_scoreLimit ||
        m_rightScore >= m_scoreLimit)
    {
        m_status = MatchStatus::Finished;
    }
}
