#include "../headers/Vec2.h"

const float PI = 3.14159;

Vec2::Vec2() {
    
}

Vec2 Vec2::Rotate(float ang) {
    Vec2 ret;
    // x' = x * cos(ang) - y * sin(ang)
    // y' = y * cos(ang) + x * sin(ang)
    // x = x * cos(ang) - y * sin(ang);
    // y = y * cos(ang) - x * sin(ang);
    // X' = (X * COS(ANGULO) ) - (Y * SEN(ANGULO) )
    // Y' = (X * SEN(ANGULO) ) + (Y * COS(ANGULO) )
    // TETA = ARCOS()
    
    ret.x =  x * cos(ang * PI/180 ) + (y) * sin(ang * PI/180);
    ret.y =  ((-1) * (x) ) * sin(ang * PI/180) + (y) * cos(ang * PI/180);
    return ret;
}

Vec2 Vec2::Soma(Vec2 v) {
    v.x = v.x + x;
    v.y = v.y + y;
    return v;
}

float Vec2::ProdEscalar(Vec2 v) {
    return ( (v.x * x) + (v.y * y) );
}