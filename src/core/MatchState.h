#pragma once

#include <optional>

enum class GoalSide
{
    Left,
    Right
};

enum class MatchStatus
{
    InProgress,
    Finished
};

class MatchState
{
public:
    MatchState();

    [[nodiscard]] int leftScore() const noexcept { return m_leftScore; }
    [[nodiscard]] int rightScore() const noexcept { return m_rightScore; }
    [[nodiscard]] MatchStatus status() const noexcept { return m_status; }

    [[nodiscard]] std::optional<GoalSide> winner() const noexcept;

    void setScoreLimit(int limit) noexcept;

    void onGoal(GoalSide side);

private:
    void checkForFinish() noexcept;

private:
    int m_leftScore = 0;
    int m_rightScore = 0;

    int m_scoreLimit = 7;
    MatchStatus m_status = MatchStatus::InProgress;
};
