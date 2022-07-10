#include "../headers/GameObject.h"

bool Rect::Contem(float mouseX, float mouseY) {
    float px, py;
    px = mouseX - x;
    py = mouseY - y;

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