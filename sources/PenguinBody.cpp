#include "../headers/PenguinBody.h"
#include "../headers/PenguinCannon.h"
#include "../headers/Sprite.h"
#include "../headers/Game.h"
#include "../headers/InputManager.h"
#include "../headers/Collider.h"
#include "../headers/Camera.h"
#include "../headers/Bullet.h"
#include "../headers/Sound.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject& associated) : Component(associated) {
    speed.x = 0;
    speed.y = 0;
    linearSpeed = 2;
    angle = 0;
    hp = 200;
    Sprite* body = new Sprite(associated, "resources/images/penguin.png");
    associated.AddComponent(body);
    Collider* cold = new Collider(associated);
    associated.AddComponent(cold);
    player = this;
    aceleracao = 15;
    speedAcc = 0;
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}

void PenguinBody::Start() {
    cout << "p body start:" << endl;
    
    GameObject* pgc = new GameObject();
    pgc->box.x = associated.box.x;
    pgc->box.y = associated.box.y;
    PenguinCannon* pc = new PenguinCannon(*pgc, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated));
    pgc->AddComponent(pc);
    pcannon = Game::GetInstance().GetCurrentState().AddObject(pgc); 
}

void PenguinBody::Update(float dt) {

    if (InputManager::GetInstance().IsKeyDown(SDLK_a)) {
        angle -= linearSpeed * dt;
        speed.x = cos(angle) * speedAcc;
        speed.y = sin(angle) * speedAcc;

    }
    if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
        angle += linearSpeed * dt;
        speed.x = cos(angle) * speedAcc;
        speed.y = sin(angle) * speedAcc;
    }
    associated.angleDeg = (angle * 180) / PI;
    // graus = radianos × 180° / PI
    ///////////////////////////////////////////////////////////////////// GIRO

    if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
        if (speedAcc < 480) {
            speedAcc += aceleracao;
            speed.x = cos(angle) * speedAcc;
            speed.y = sin(angle) * speedAcc;
        }
    }
    if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
        if (speedAcc > -480) {
            speedAcc -= aceleracao;
            speed.x = cos(angle) * speedAcc;
            speed.y = sin(angle) * speedAcc;
        }
    }
    ///////////////////////////////////////////////////////////////////// ACELERA

    if (InputManager::GetInstance().KeyRelease(SDLK_w)) {
        desacelerarFrente = true;
    }
    if (InputManager::GetInstance().KeyRelease(SDLK_s)) {
        desacelerarBack = true;
    }

    if(desacelerarFrente && speedAcc > 0) {
        if (InputManager::GetInstance().IsKeyDown(SDLK_w)) {
            desacelerarFrente = false;
        }
        // cout << "freiando..." << endl;
        speedAcc -= aceleracao;
        speed.x = cos(angle) * speedAcc;
        speed.y = sin(angle) * speedAcc;
        if (speedAcc == 0) {
            speed.x = 0;
            speed.y = 0;
            desacelerarFrente = false;
            //cout << "parou" << endl;
        }
    }

    if(desacelerarBack && speedAcc < 0) {
        if (InputManager::GetInstance().IsKeyDown(SDLK_s)) {
            desacelerarBack = false;
        }
        // cout << "freiando...re" << endl;
        speedAcc += aceleracao;
        
        speed.x = cos(angle) * speedAcc;
        speed.y = sin(angle) * speedAcc;
        if (speedAcc == 0) {
            speed.x = 0;
            speed.y = 0;
            desacelerarBack = false;
            //cout << "parou" << endl;
        }
    }
    ///////////////////////////////////////////////////////////////////// DESACELERA

    
    //cout << "speed X: " << speed.x << " speed Y: " << speed.y << " angle: " << angle << endl;
    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    if(associated.box.x > 1600) {
        associated.box.x = 1600;
    }
    if(associated.box.x < -192) {
        associated.box.x = -192;
    }

    if(associated.box.y > 1472) {
        associated.box.y = 1472;
    }
    if(associated.box.y < -192) {
        associated.box.y = -192;
    }
    cout << "pos X: " << associated.box.x << " pos Y: " << associated.box.y << " angle: " << angle << endl;

    //cout << "hp Pinguin: " << hp << endl;
    if (hp <= 0) {
        Camera::Unfollow();
        GameObject* expl = new GameObject();
        Sprite* ex = new Sprite(*expl, "resources/images/penguindeath.png", 5, 0.08, 0.4);
        expl->AddComponent(ex);
        Sound* som = new Sound(*expl, "resources/sounds/boom_pg.wav");
        som->Play();
        expl->AddComponent(som);
        expl->box.x = associated.box.GetCenter().x - ex->GetWidth()/2;
        expl->box.y = associated.box.GetCenter().y - ex->GetHeight()/2;
        Game::GetInstance().GetCurrentState().AddObject(expl);
        associated.RequestDelete();
    }

}

void PenguinBody::Render() {

}

bool PenguinBody::Is(string type) {
    string pb = "PenguinBody";
    if (type == pb || Being::Is(type) ){
        return true;
    } else {
        return false;
    }
}

void PenguinBody::NotifyCollision(GameObject& other) {
    if (!other.GetComponent("Being")) {
        Component* cp = other.GetComponent("Bullet");
        if (cp) {
            Bullet* bl = (Bullet*) cp;
            if (!bl->targetsPlayer) {
                //cout << "Bateu no PenguinBody: W: " << other.box.w << endl;
                hp -= 10;
                other.RequestDelete();
                //cout << "hp Pinguin: " << hp << endl;
            }
        }
        
    }
}

Rect PenguinBody::GetBoxPenguin() {
    return associated.box;
}