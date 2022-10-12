#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

bool Rect::Contem(float mouseX, float mouseY) {
    float px, py;
    px = mouseX - x;
    py = mouseY - y;
    
    if(px >= 0 && px <= w) {
        if(py >= 0 && py <= h){
            return true;
        }
    }
    return false;
}

Vec2 Rect::GetCenter() {
    Vec2 center(x + w/2.0, y + h/2.0);
    return center;
}

Vec2 Rect::PosCenter() {
    Vec2 center(x - w/2.0, y - h/2.0);
    return center;
}