#include "Time.h"
#include <cmath>

void Time::update() {
    const auto now = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diff = now - m_last;
    m_delta = std::min(diff.count(), 0.25);
    m_last = now;
}
