#include "../headers/PenguinCannon.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"
#include "../headers/Bullet.h"
#include "../headers/Game.h"
#include "../headers/Collider.h"
#include "../headers/Sound.h"

PenguinCannon::PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody) : Component(associated) {
    angle = 0;
    pbody = penguinBody;
    Sprite* cannon = new Sprite(associated, "resources/images/cubngun_tranco_animation.png", 4, 0.03);
    cannon->selectOneFrame = true;
    associated.AddComponent(cannon);
    Collider* cold = new Collider(associated);
    associated.AddComponent(cold);
    maxDistance = 600;
    damage = 15;
    recarga = new Sound(associated, "resources/sounds/recarrega.wav");
}

void PenguinCannon::Update(float dt) {
    Vec2 xy(0,0);
    time.Update(dt);
    
    if(pbody.lock()) {

        associated.box.x = (pbody.lock()->box.x + pbody.lock()->box.w/2) - associated.box.w/2;
        associated.box.y = (pbody.lock()->box.y + pbody.lock()->box.h/2) - associated.box.h/2;

        xy.x = InputManager::GetInstance().GetMouseX() + Camera::pos.x;
        xy.y = InputManager::GetInstance().GetMouseY() + Camera::pos.y;
        angle = atan2(xy.y - pbody.lock()->box.GetCenter().y, xy.x - pbody.lock()->box.GetCenter().x);
        
        associated.angleDeg = (angle * 180) / PI;

        
        if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
            cout << "Atira.." << endl;
            if (municao > 0) {
                Component* cp = associated.GetComponent("Sprite");
                if (cp) {
                    sp = (Sprite*) cp;
                    sp->selectOneFrame = false;
                }
                Shoot();
                municao--;
                recarrega = false;
                cooldown = false;
            }
        }
        if(sp) {
            //cout << "sp" << endl;
            arranque.Update(dt);
            if (arranque.Get() > 0.4) {
                sp->selectOneFrame = true;
                arranque.Restart();
                sp = nullptr;
            }
        }

    // cout << time.Get() << " municao: " << municao << endl;
    if (municao == 0) {
        //cout << "recarga" << endl;
        recarrega = true;
    }
    if (recarrega && !cooldown) {
        time.Restart();
        cooldown = true;
        recarga->Play();
    }
    if (recarrega) {
        if (time.Get() > 1.5) {
            municao = 10;
            recarrega = false;
        }
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
    if (type == pg || Being::Is(type)){
        return true;
    } else {
        return false;
    }
}

void PenguinCannon::Shoot() {
    float speed = maxDistance / 0.5;  
    GameObject* bullet = new GameObject();
    
    
    bullet->angleDeg = (angle * 180) / PI;
    Bullet* bul = new Bullet(*bullet, angle, speed, damage, maxDistance, true, 4, "resources/images/penguinbullet.png");

    bullet->box.x = (pbody.lock()->box.x + pbody.lock()->box.w/2) - bullet->box.w/2 + cos(angle) * associated.box.w/2.0;
    bullet->box.y = (pbody.lock()->box.y + pbody.lock()->box.h/2) - bullet->box.h/2 + sin(angle) * associated.box.w/2.0;
    bullet->AddComponent(bul);
    
    // cout << "bullet X: " << bullet->box.x << " bullet Y: " << bullet->box.y << endl;
    
    // Sound* som = new Sound(*bullet, "resources/sounds/tiro.wav");
    // som->Play();
    Sound* som = new Sound(*bullet, "resources/sounds/canhao.wav");
    som->Play();
    bullet->AddComponent(som);
    Game::GetInstance().GetCurrentState().AddObject(bullet);
}

void PenguinCannon::NotifyCollision(GameObject& other) {
    if (!other.GetComponent("Being")) {
        Component* cp = other.GetComponent("Bullet");
        if (cp) {
            Bullet* bl = (Bullet*) cp;
            if (!bl->targetsPlayer) {
                //cout << "Bateu no PenguinCannon: W: " << other.box.w << endl;
            }
        }
        
    }
}