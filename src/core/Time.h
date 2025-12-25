#pragma once

#include <chrono>

class Time
{
public:
    Time() : m_last(std::chrono::high_resolution_clock::now())
    {
    }

    void update();

    [[nodiscard]] double delta() const { return m_delta; }

private:
    std::chrono::high_resolution_clock::time_point m_last;
    double m_delta = 0.0;
};
