#pragma once

struct Rink {
    float left   = -1.88f;
    float right  =  1.88f;
    float top    =  1.0f;
    float bottom = -1.0f;

    float width() const { return right - left; }
    float height() const { return top - bottom; }
};
