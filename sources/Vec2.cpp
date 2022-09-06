#include "../headers/Vec2.h"

Vec2::Vec2() {
    
}

Vec2 Vec2::Rotate(float ang) {
    // x' = x * cos(ang) - y * sin(ang)
    // y' = y * cos(ang) + x * sin(ang)
    x = x * cos(ang) - y * sin(ang);
    y = y * cos(ang) - x * sin(ang);
    return *this;
}

Vec2 Vec2::Soma(Vec2 v) {
    v.x = v.x + x;
    v.y = v.y + y;
    return v;
}