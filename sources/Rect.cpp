#include "../headers/GameObject.h"

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