#pragma once

#include <variant>
#include <vector>
#include "MatchState.h"

enum class GameEventType
{
    Goal,
    RoundReset,
    MatchReset,
    MatchFinished
};

struct GoalEvent
{
    GoalSide side;
};

struct RoundResetEvent
{

};

struct MatchResetEvent
{

};

struct MatchFinishedEvent
{
    GoalSide winner;
};

using GameEventPayload = std::variant<
    GoalEvent,
    RoundResetEvent,
    MatchResetEvent,
    MatchFinishedEvent
>;

struct GameEvent
{
    GameEventType type;
    GameEventPayload payload;

    static GameEvent makeGoal(const GoalSide side)
    {
        return { GameEventType::Goal, GoalEvent{ side } };
    }

    static GameEvent makeRoundReset()
    {
        return { GameEventType::RoundReset, RoundResetEvent{} };
    }

    static GameEvent makeMatchReset()
    {
        return { GameEventType::MatchReset, MatchResetEvent{} };
    }

    static GameEvent makeMatchFinished(const GoalSide winner)
    {
        return { GameEventType::MatchFinished, MatchFinishedEvent{ winner } };
    }
};

class GameEventQueue
{
public:
    GameEventQueue() = default;

    inline void push(GameEvent event)
    {
        m_events.emplace_back(std::move(event));
    }

    [[nodiscard]] inline bool empty() const noexcept
    {
        return m_events.empty();
    }

    inline std::vector<GameEvent> consume()
    {
        std::vector<GameEvent> out;
        out.swap(m_events);
        return out;
    }

    inline void clear() noexcept
    {
        m_events.clear();
    }

private:
    std::vector<GameEvent> m_events;
};