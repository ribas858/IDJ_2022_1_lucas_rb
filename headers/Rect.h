#ifndef RECT_H
#define RECT_H

#include "../headers/base_includes.h"

class Rect {

    public:
        float x, y, w, h;

        bool Contem(float mouseX, float mouseY);
        class Vec2 GetCenter();
        class Vec2 PosCenter();

    private:

};

#endif