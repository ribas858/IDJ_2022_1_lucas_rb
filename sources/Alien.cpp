#include "../headers/Alien.h"
#include "../headers/Sprite.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"
#include "../headers/Minion.h"
#include "../headers/Game.h"
#include "../headers/State.h"
#include "../headers/Sound.h"
#include "../headers/Collider.h"
#include "../headers/Bullet.h"
#include "../headers/PenguinBody.h"
#include "../headers/GameData.h"

Vec2 Alien::inicialPos(0,0);
Vec2 Alien::desloc(0,0);
Vec2 Alien::fimDesloc(0,0);
int Alien::flag = 0;



Alien::Alien(GameObject & associated, int nMinions, float timeOffset) : Component(associated), nMinions(nMinions), timeOffset(timeOffset) {

    Sprite* alienSprite = new Sprite(associated, "resources/images/alien.png");
    // alienSprite->SetScale(2,2);
    associated.AddComponent(alienSprite);
    Sound* som = new Sound(associated, "resources/sounds/mini.wav");
    associated.AddComponent(som);
    Collider* cold = new Collider(associated);
    associated.AddComponent(cold);
    hp = 100;

    associated.box.x = associated.box.x - (associated.box.w / 2);
    associated.box.y =  associated.box.y - (associated.box.h / 2);


    //cout << "alien w: " << associated.box.w << " alien h: " << associated.box.h << endl;
    //cout << "alien x: " << associated.box.x << " alien y: " << associated.box.y << endl;
    speed.x = 0;
    speed.y = 0;
    GameData::alienCount++;
    id = GameData::alienCount;
    state = AlienState::RESTING;
}

Alien::~Alien() {
    for (int i = 0; i < minionArray.size(); i++) {
        minionArray[i].reset();
    }
    minionArray.clear();
    GameData::alienCount--;
}

void Alien::Start() {
    cout << "start alien" << " alien id: " << id << " alienCount: " << GameData::alienCount << endl;
    //
    for (int i = 1; i <= nMinions; i++) {
        GameObject* minion = new GameObject();
        const float MIN_RAND = 1.0, MAX_RAND = 1.5;
        const float range = MAX_RAND - MIN_RAND;
        // cout << range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND << endl;

        float scale = range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND;
        Vec2 s(scale,scale);
        //Vec2 s(1,1);
        
        if (i == 1) {
            Minion* mini = new Minion(*minion, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated), 4, true, i, nMinions, s);
            minion->AddComponent(mini);
        } else {
            Minion* mini = new Minion(*minion, Game::GetInstance().GetCurrentState().GetObjectPtr(&associated), 4, false, i, nMinions, s);
            minion->AddComponent(mini);
        }

        minionArray.push_back(Game::GetInstance().GetCurrentState().AddObject(minion));
        
    }
    cout << endl;

}

void Alien::Update(float dt) {

    //cout << "alien x: " << associated.box.x << " alien y: " << associated.box.y << " alienCount: " << alienCount << endl;
    associated.angleDeg++;
    if (associated.angleDeg == 360) {
        associated.angleDeg = 0;
    }
    if (PenguinBody::player) { 
        if (state == AlienState::RESTING) {
            restTimer.Update(dt);
            tiros.Update(dt);

            if (tiros.Get() > 0.8) {
                tiros.Restart();
                NewShoot(PenguinBody::player->GetBoxPenguin().GetCenter());
            }
            if (restTimer.Get() > 5 * timeOffset) {
                destination = PenguinBody::player->GetBoxPenguin().GetCenter();
                state = AlienState::MOVING;
                restTimer.Restart();
            }
        }
        if (state == AlienState::MOVING) {
            restTimer.Update(dt);
            if (flag == 0) {
                inicialPos.x = associated.box.x;
                inicialPos.y = associated.box.y;
                desloc.x = destination.x - (associated.box.x + associated.box.w/2);
                desloc.y = destination.y - (associated.box.y + associated.box.h/2);
                flag = 1;
                counTiros = 0;
            }
            speed.x = desloc.x / (1/dt);
            speed.y = desloc.y / (1/dt);

            if (desloc.x < 0) {
                if (fimDesloc.x == 0) {
                    associated.box.x += speed.x;
                    if (associated.box.GetCenter().x < destination.x) {
                        // cout << "x neg -: +1" << endl;
                        fimDesloc.x++;
                    }
                }
            } else if (desloc.x > 0) {
                if (fimDesloc.x == 0) {
                    associated.box.x += speed.x;
                    if (associated.box.GetCenter().x > destination.x) {
                        // cout << "x posit : +1" << endl;
                        fimDesloc.x++;
                    }
                }
            }
            if (desloc.y < 0) {
                if (fimDesloc.y == 0) {
                    associated.box.y += speed.y;
                    if (associated.box.GetCenter().y < destination.y) {
                        // cout << "y neg -: +1" << endl;
                        fimDesloc.y++;
                    }
                }
            } else if (desloc.y > 0) {
                if (fimDesloc.y == 0) {
                    associated.box.y += speed.y;
                    if (associated.box.GetCenter().y > destination.y) {
                        // cout << "y posit : +1" << endl;
                        fimDesloc.y++;
                    }
                }
            }
            
            if (restTimer.Get() > 0.5) {
                destination = PenguinBody::player->GetBoxPenguin().GetCenter();
                NewShoot(destination);
                if (fimDesloc.x == 0 || fimDesloc.y == 0) {
                    restTimer.Restart();
                }
                counTiros++;
            }

            if (fimDesloc.x == 1 && fimDesloc.y == 1) {
                if (restTimer.Get() > 0.5) {
                    //cout << "\nFim Desloc. X: " << fimDesloc.x << " | Fim Desloc. y: " << fimDesloc.y << " | Tiros: " << counTiros << endl;
                    //printf("Pos X0: %.6f | Pos Y0: %.6f\n", inicialPos.x, inicialPos.y);
                    //printf("Pos X: %.6f | Pos Y: %.6f\n", destination.x, destination.y);
                    //printf("Cam X: %.6f | Cam Y: %.6f\n", Camera::pos.x, Camera::pos.y);
                    
                    fimDesloc.x = 0;
                    fimDesloc.y = 0;
                    flag = 0;
                    speed.x = 0;
                    speed.y = 0;
                    destination = PenguinBody::player->GetBoxPenguin().GetCenter();
                    NewShoot(destination);
                    restTimer.Restart();
                    state = AlienState::RESTING;
                }
            }
        }
    } else {
        //cout << "Fim de jogo" << endl;
    }
    //cout << "hp: " << hp << endl;
    if (hp <= 0) {
        GameObject* expl = new GameObject();
        Sprite* ex = new Sprite(*expl, "resources/images/aliendeath_fire2.png", 8, 0.08, 0.8);
        expl->AddComponent(ex);
        Sound* som = new Sound(*expl, "resources/sounds/boom.wav");
        som->Play();
        expl->box.x = associated.box.GetCenter().x - ex->GetWidth()/2;
        expl->box.y = associated.box.GetCenter().y - ex->GetHeight()/2;
        expl->AddComponent(som);
        Game::GetInstance().GetCurrentState().AddObject(expl);
        associated.RequestDelete();
    }
}

void Alien::Render() {

}

bool Alien::Is(string type) {
    string alien = "Alien";
    if (type == alien || Being::Is(type) ){
        return true;
    } else {
        return false;
    }
}

Vec2 Alien::GetSpeed() {
    return speed;
}

Vec2 Alien::GetDesloc() {
    return desloc;
}

void Alien::NotifyCollision(GameObject& other) {
    if (!other.GetComponent("Being")) {
        Component* cp = other.GetComponent("Bullet");
        if (cp) {
            Bullet* bl = (Bullet*) cp;
            if (bl->targetsPlayer) {
                //cout << "Bateu no Alien: W: " << other.box.w << endl;
                hp -= 10;
                GameData::pontos += 5;

                GameObject* expl = new GameObject();
                Sprite* ex = new Sprite(*expl, "resources/images/penguindeath.png", 5, 0.08, 0.4);
                ex->SetScale(0.5, 0.5);
                expl->AddComponent(ex);
                // Sound* som = new Sound(*expl, "resources/sounds/boom_pg.wav");
                // som->Play();
                // expl->AddComponent(som);
                expl->box.x = other.box.GetCenter().x - ex->GetWidth()/2;
                expl->box.y = other.box.GetCenter().y - ex->GetHeight()/2;
                Game::GetInstance().GetCurrentState().AddObject(expl);

                other.RequestDelete();
                //cout << "hp Alien: " << hp << endl;
            }
        }
        
    }
}

void Alien::NewShoot(Vec2 destination) {
    if (!minionArray.empty()) {
        int id = 0;

        float deslocEscalar = 0;
        float min = 99999999;
        for (int i=0; i<minionArray.size(); i++) {
            float x = destination.x - minionArray[i].lock()->box.x;
            float y = destination.y - minionArray[i].lock()->box.y;
            deslocEscalar = sqrt(pow(x, 2) + pow(y, 2));
            if (deslocEscalar < min) {
                min = deslocEscalar;
                id = i;
            }
        }
        //cout << "Minion Mais Perto: " << id << " Distancia: " << min << endl;
        
        if (min < 400) {
            if(auto mini = minionArray[id].lock()) {
                //cout << "minon shoot" << endl;
                Minion* minion = (Minion*) mini->GetComponent("Minion");
                
                if(minion) {
                    
                    minion->Shoot(destination);
                    
                }
            }
        }
    }
}

void Alien::CleanGlobals() {
    inicialPos = {0, 0};
    desloc = {0, 0};
    fimDesloc = {0, 0};
    flag = 0;
}