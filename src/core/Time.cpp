#include "Time.h"

void Time::update() {
    const auto now = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diff = now - m_last;
    m_delta = diff.count();
    m_last = now;
}
