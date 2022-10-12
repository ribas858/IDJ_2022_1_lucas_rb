#include "../headers/Vec2.h"

Vec2::Vec2() {
    
}

Vec2 Vec2::Rotate(float ang) {
    Vec2 ret;
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

Vec2 Vec2::operator+(const Vec2& rhs) const {
   return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
   return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator*(const float rhs) const {
   return Vec2(x * rhs, y * rhs);
}