#include "../headers/Minion.h"
#include "../headers/Sprite.h"
#include "../headers/Resources.h"

const float PI = 3.14159;
int Minion::flag = 0;
 
Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg) : alienCenter(*alienCenter.lock()) , arc(arcOffsetDeg), Component(associated) {
    Sprite* minionSprite = new Sprite(associated, "resources/images/minion.png");
    associated.AddComponent(minionSprite);
    // origin.x = Minion::alienCenter.box.x - associated.box.w/2;
    // origin.y = Minion::alienCenter.box.y - associated.box.h/2;
    origin.x = 0; 
    origin.y = 0;
    associated.box.x = 0;
    associated.box.y = 0;
    
    
}
        
void Minion::Update(float dt) {
    
    float raio = associated.box.w / 2;


    arc = 2;
    // cout << "Raio: " << raio << endl;
    
    float xl =  (associated.box.x - origin.x) * cos(arc * PI/180 ) + (associated.box.y -origin.y) * sin(arc * PI/180);
    float yl =  ((-1) * (associated.box.x - origin.x) ) * sin(arc * PI/180) + (associated.box.y - origin.y) * cos(arc * PI/180);
    cout << "xl: " << xl << " yl: " << yl << endl;

    if (xl == 0 && yl == 0) {
        cout << "foi" << endl;
        associated.box.x = 100;
    } else {
        if (flag == 0) {
            cout << "flag" << endl;
            associated.box.x = 0;
            origin.x = 300; 
            origin.y = 300;
            flag = 1;
        }
        associated.box.x = xl;
        associated.box.y = yl;
    }
    
    
    
    
    //cout << "mini x: " << associated.box.x << " mini y: " << associated.box.y << endl;
    //cout << "alien x: " << Minion::alienCenter.box.x << " alien y: " << Minion::alienCenter.box.y << endl;
    //cout << "alienCenter x: " << Minion::alienCenter.box.x + (Minion::alienCenter.box.w / 2) << " alienCenter y: " << Minion::alienCenter.box.y + (Minion::alienCenter.box.h / 2) << endl;

    
    
    associated.box.x += origin.x;
    associated.box.y += origin.y;
    // cout << "x: " << associated.box.x << " y: " << associated.box.y << endl;

    

}

void Minion::Render() {

}

bool Minion::Is(string type) {
    return false; // test compile
}

void Minion::Shoot(Vec2 target) {
    
}