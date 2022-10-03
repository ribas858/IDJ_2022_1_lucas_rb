#include "../headers/PenguinCannon.h"
#include "../headers/Sprite.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"
#include "../headers/Bullet.h"
#include "../headers/Game.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) : Component(associated) {
    angle = 0;
    pbody = penguinBody;
    Sprite* cannon = new Sprite(associated, "resources/images/cubngun.png");
    associated.AddComponent(cannon);
    maxDistance = 600;
    damage = 15;
}

void PenguinCannon::Update(float dt) {
    Vec2 xy(0,0);

    if(pbody.lock()) {

        associated.box.x = (pbody.lock()->box.x + pbody.lock()->box.w/2) - associated.box.w/2;
        associated.box.y = (pbody.lock()->box.y + pbody.lock()->box.h/2) - associated.box.h/2;

        xy.x = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
        xy.y = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
        angle = atan2(xy.y - pbody.lock()->box.y, xy.x - pbody.lock()->box.x);
        
        associated.angleDeg = (angle * 180) / PI;

        if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
            cout << "Atira.." << endl;
            Shoot();
        }

    } else {
        cout << "Pinguin Body morreu..." << endl;
        associated.RequestDelete();
    }
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(string type) {
    string pg = "PenguinCannon";
    if (type == pg){
        return true;
    } else {
        return false;
    }
}

void PenguinCannon::Shoot() {
    float speed = maxDistance / 0.5;  
    GameObject* bullet = new GameObject();
    
    
    bullet->angleDeg = (angle * 180) / PI;
    Bullet* bul = new Bullet(*bullet, angle, speed, damage, maxDistance, "resources/images/penguinbullet.png");

    bullet->box.x = (pbody.lock()->box.x + pbody.lock()->box.w/2) - bullet->box.w/2 + cos(angle) * associated.box.w/2.0;
    bullet->box.y = (pbody.lock()->box.y + pbody.lock()->box.h/2) - bullet->box.h/2 + sin(angle) * associated.box.w/2.0;
    bullet->AddComponent(bul);
    
    // cout << "bullet X: " << bullet->box.x << " bullet Y: " << bullet->box.y << endl;
    
    // Sound* som = new Sound(*bullet, "resources/sounds/tiro.wav");
    // som->Play();
    Game::GetInstance().GetState().AddObject(bullet);
}