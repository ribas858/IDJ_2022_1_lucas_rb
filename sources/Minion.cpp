#include "../headers/Minion.h"
#include "../headers/Sprite.h"
#include "../headers/InputManager.h"
#include "../headers/Bullet.h"
#include "../headers/Game.h"

const float PI = 3.14159;

int Minion::nextMiniLiberado = 0;
int Minion::lastMiniLiberado = 0;
int Minion::resetPos = 0;

int Minion::allFree = 0;
 
Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg, bool lib, int id, int nMini, Vec2 scale) : id(id), liberado(lib), arc(arcOffsetDeg), alienCenter(alienCenter), Component(associated) {
    numMinions = nMini;
    Sprite* minionSprite = new Sprite(associated, "resources/images/minion.png");
    minionSprite->SetScale(scale.x, scale.y);
    associated.AddComponent(minionSprite);

    associated.box.x = 0;
    associated.box.y = 0;
    origin.x = 0; 
    origin.y = 0;

    xyLinha.x = 0;
    xyLinha.y = 0;
    xy.x = 0;
    xy.y = 0;
    diametro = 110;
    releaseLimit = (nMini * 10) - 10;

    sourceShoot.x = 0;
    sourceShoot.y = 0;
    ang = 90;

    if (liberado) {
        lastMiniLiberado = id;
        InputManager::GetInstance().SetLoadMinions() = 1;
    }
}
        
void Minion::Update(float dt) {

    if(auto ali = alienCenter.lock()) {
        
        //cout << "arc: " << arc << endl;

        if (liberado && lastMiniLiberado == id && resetPos == 1) {
            
            resetPos = 0;
            associated.box.x = diametro;
            associated.box.y = 0;
            origin.x = 0; 
            origin.y = 0;
        }
        
        // cout << "Liberadodo: " << liberado << " ANTESSSS | x: " << associated.box.x << " y: " << associated.box.y << endl;

        xy.x = associated.box.x - origin.x;
        xy.y = associated.box.y - origin.y;
        xyLinha = xy.Rotate(arc);

        // xyLinha.x =  (associated.box.x - origin.x) * cos(arc * PI/180 ) + (associated.box.y -origin.y) * sin(arc * PI/180);
        // xyLinha.y =  ((-1) * (associated.box.x - origin.x) ) * sin(arc * PI/180) + (associated.box.y - origin.y) * cos(arc * PI/180);
        // cout << "xyLinha.x: " << xyLinha.x << " yl: " << xyLinha.y << endl;

        if (xyLinha.x == 0 && xyLinha.y == 0) {
            // cout << "x linha e y linha zerados" << endl;
            if (liberado) {
                associated.box.x = diametro;
                associated.box.y = 0;
            } else {
                
                float x = (alienCenter.lock()->box.x + (alienCenter.lock()->box.w / 2));
                float y = (alienCenter.lock()->box.y + (alienCenter.lock()->box.h / 2));
                
                associated.box.x = x - (associated.box.w / 2) + diametro;
                associated.box.y = y - associated.box.h / 2;
            }
            // origin.x = 0; 
            // origin.y = 0;
            
        } else {

            if (xyLinha.x < releaseLimit) {
                if (liberado && lastMiniLiberado == id) {
                    nextMiniLiberado = 1;
                    
                }
            }

            if(!liberado && nextMiniLiberado == 1) {
                lastMiniLiberado = id;
                liberado = true;
                resetPos = 1;
                nextMiniLiberado = 0;
                InputManager::GetInstance().SetLoadMinions()++;
            } 
            
            if (liberado) {
                
                float x = (alienCenter.lock()->box.x + (alienCenter.lock()->box.w / 2));
                float y = (alienCenter.lock()->box.y + (alienCenter.lock()->box.h / 2));
                // cout << "alienC x: " << x << " alienC y: " << y << endl;
                origin.x = x - associated.box.w / 2;
                origin.y = y - associated.box.h / 2;
            
                associated.box.x = xyLinha.x;
                associated.box.y = xyLinha.y;

                associated.box.x += origin.x;
                associated.box.y += origin.y;
            }
            
        }

        if (allFree == 1) {
            arc = 2;
            ang += - 2;
        } else {
            if (liberado) {
                ang += - 6;
            }
        }
        associated.angleDeg = ang;

        // cout << " ang: " << ang << endl;

        // cout << "Id: " << id << " | x: " << associated.box.x << " y: " << associated.box.y << endl << endl;
        // cout << "Minions Liberados: " << InputManager::GetInstance().GetLoadMinions() << endl;
        
        if (InputManager::GetInstance().GetLoadMinions() == numMinions) {
            allFree = 1;
        }
        
    } else {
        // cout << "Alien morreu.." << endl;
        associated.RequestDelete();
    }
}

void Minion::Render() {

}

bool Minion::Is(string type) {
    string minion = "Minion";
    if (type == minion){
        return true;
    } else {
        return false;
    }
}

void Minion::Shoot(Vec2 target) {
    Vec2 desloc;
    int damage = 10;
    float maxDistance = 600;
    float angle, speed;
    
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        sourceShoot.x = associated.box.x;
        sourceShoot.y = associated.box.y;
        // cout << "boom sourceShoot x: " << sourceShoot.x << " sourceShoot y: " << sourceShoot.y << endl;
    }

    cout << "Alvo: x:" << target.x << " | y: " << target.y << endl;
    cout << "Fonte: x:" << sourceShoot.x << " | y: " << sourceShoot.y << endl;

    
    desloc.x = target.x - sourceShoot.x;
    desloc.y = target.y - sourceShoot.y;

    float deslocEscalar = sqrt(pow(desloc.x, 2) + pow(desloc.y, 2));

    speed = maxDistance / 0.5;

    angle = atan2(desloc.y, desloc.x);
    // cout << "Deslocamento: x:" << desloc.x << " | y: " << desloc.y << endl;
    // cout << "angle: " << (angle * 180) / PI << endl;
    
    GameObject* bullet = new GameObject();
    bullet->box.x = sourceShoot.x;
    bullet->box.y = sourceShoot.y;
    bullet->angleDeg = (angle * 180) / PI;
    Bullet* bul = new Bullet(*bullet, angle, speed, damage, maxDistance, "resources/images/minionbullet1.png");
    bullet->AddComponent(bul);
    
    Game::GetInstance().GetState().AddObject(bullet);
}