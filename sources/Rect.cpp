#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

bool Rect::Contem(float mouseX, float mouseY) {
    float px, py;
    px = mouseX - x;
    py = mouseY - y;

    // cout << "mousex:" << mouseX << " x:" << x << endl;
    // cout << " mousey:" << mouseY << " y:" << y<< endl;

    // cout << "w:" << w;
    // cout << " h:" << h << endl;
    // cout << "px:" << px;
    // cout << " py:" << py << endl;
    
    if(px >= 0 && px <= w) {
        //cout << "if 1" << endl;
        if(py >= 0 && py <= h){
            //cout << "if 2" << endl;
            return true;
        }
    }
    return false;
}

Vec2 Rect::GetCenter() {
    Vec2 center(x + w/2.0, y + h/2.0);
    return center;
}