#ifndef VEC2_H
#define VEC2_H

#include "../headers/base_includes.h"

class Vec2 {

    public:
        Vec2();
        float x, y;

        Vec2(float xi, float yi) : x(xi), y(yi) {}

        Vec2 Rotate(float ang);
        Vec2 Soma(Vec2 v);
        float ProdEscalar(Vec2 v);

    private:
};

#endif