#include "../headers/PenguinCannon.h"
#include "../headers/Sprite.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) : Component(associated) {
    angle = 0;
    pbody = penguinBody;
    Sprite* cannon = new Sprite(associated, "resources/images/cubngun_pt.png");
    associated.AddComponent(cannon);
}

void PenguinCannon::Update(float dt) {

    if(pbody.lock()) {

        associated.box.x = (pbody.lock()->box.x + pbody.lock()->box.w/2) - associated.box.w/2;
        associated.box.y = (pbody.lock()->box.y + pbody.lock()->box.h/2) - associated.box.h/2;
        float x = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
        float y = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
        angle = atan2(y - associated.box.y, x - associated.box.x);
        // cout << "Mouse x: " << x << " Mouse y: " <<  y << " angle: " << angle << endl;
        associated.angleDeg = (angle * 180) / PI;

    } else {
        cout << "Pinguin Body morreu..." << endl;
        associated.RequestDelete();
    }
}

void PenguinCannon::Render() {

}

bool PenguinCannon::Is(string type) {
    return false;
}

void PenguinCannon::Shoot() {
    
}