#include "../headers/Minion.h"
#include "../headers/Sprite.h"
#include "../headers/InputManager.h"
#include "../headers/Bullet.h"
#include "../headers/Game.h"
#include "../headers/Sound.h"
#include "../headers/Collider.h"
#include "../headers/Camera.h"
#include "../headers/Alien.h"


vector<int> Minion::nextMiniLiberado = {};
vector<int> Minion::lastMiniLiberado = {};
vector<int> Minion::resetPos = {};

vector<int> Minion::allFree = {};

vector<float> Minion::limitePisca = {};
vector<float> Minion::somaScale = {};
 
Minion::Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg, bool lib, int id, int nMini, Vec2 scale) : id(id), liberado(lib), arc(arcOffsetDeg), alienCenter(alienCenter), Component(associated) {
    numMinions = nMini;
    originalScale = scale;
    
    Sprite* minionSprite = new Sprite(associated, "resources/images/minion.png");
    minionSprite->SetScale(scale.x, scale.y);
    associated.AddComponent(minionSprite);
    Collider* cold = new Collider(associated);
    associated.AddComponent(cold);
    

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
        InputManager::GetInstance().GetLoadMinions()->push_back(1);
        lastMiniLiberado.push_back(id);
        nextMiniLiberado.push_back(0);
        resetPos.push_back(0);
        allFree.push_back(0);

        limitePisca.push_back(0);
        somaScale.push_back(0);

        Component* cp = alienCenter.lock()->GetComponent("Sound");
        if (cp) {
            Sound* som = (Sound*)cp;
            som->Play();
        }
    }
}
        
void Minion::Update(float dt) {

    Component* cp = alienCenter.lock()->GetComponent("Alien");
    if (cp) {
        Alien* al = (Alien*)cp;
        cout << "a mini id: " << id << " alien id: " << al->id << " loadMinons: " << InputManager::GetInstance().GetLoadMinions()->at(idAlien) << endl;
        idAlien = al->id - 1;
         
    }
    

    if(auto ali = alienCenter.lock()) {
        
        Sprite* s = (Sprite*) associated.GetComponent("Sprite");
        if(!liberado) {
            float intervalo = 0.01;
            if (limitePisca.at(idAlien) < 20 * dt) {
                somaScale.at(idAlien) += intervalo;
                s->SetScaleRender(originalScale.x - intervalo, originalScale.y - intervalo);
            } else {
                if (limitePisca.at(idAlien) > 40 * dt) {
                    limitePisca.at(idAlien) = 0;
                    somaScale.at(idAlien) = 0;
                }
                //cout << "somaScale: " << somaScale << " ori x: " << originalScale.x - somaScale << endl;
                
                s->SetScaleRender(originalScale.x - somaScale.at(idAlien) + intervalo, originalScale.y - somaScale.at(idAlien) + intervalo);
                somaScale.at(idAlien) -= intervalo;
            }
            limitePisca.at(idAlien) += dt;
            //cout << "limitePisca: " << limitePisca << endl;
        } 
        else if (allFree.at(idAlien) == 0) {
            //cout << "set original" << endl;
            s->SetScaleRender(originalScale.x, originalScale.y);
        }

        

        
        //cout << "arc: " << arc << endl;
        
        if (liberado && lastMiniLiberado.at(idAlien) == id && resetPos.at(idAlien) == 1) {
            
            resetPos.at(idAlien) = 0;
            associated.box.x = diametro;
            associated.box.y = 0;
            origin.x = 0; 
            origin.y = 0;
        }
        // // cout << "Liberadodo: " << liberado << " ANTESSSS | x: " << associated.box.x << " y: " << associated.box.y << endl;

        xy.x = associated.box.x - origin.x;
        xy.y = associated.box.y - origin.y;
        xyLinha = xy.Rotate(arc);

        if (xyLinha.x == 0 && xyLinha.y == 0) {
            // cout << "x linha e y linha zerados" << endl;
            if (liberado) {
                // associated.box.x = (512.0 + (alienCenter.lock()->box.w / 2)) - associated.box.w/2;
                // associated.box.y = (300.0 + (alienCenter.lock()->box.h / 2)) - associated.box.h/2;
                associated.box.x = diametro;
                associated.box.y = 0;
            } else {
                float x = (alienCenter.lock()->box.x + (alienCenter.lock()->box.w / 2));
                float y = (alienCenter.lock()->box.y + (alienCenter.lock()->box.h / 2));
                associated.box.x = x - associated.box.w/2 + diametro;
                associated.box.y = y - associated.box.h/2;
            }
        
        } else {
            
            if (xyLinha.x < releaseLimit) {
                if (liberado && lastMiniLiberado.at(idAlien) == id) {
                    nextMiniLiberado.at(idAlien) = 1;
                }
            }

            
            if(!liberado && nextMiniLiberado.at(idAlien) == 1) {
                cout << "liberando.." << endl;
                Component* cp = alienCenter.lock()->GetComponent("Sound");
                if (cp) {
                    Sound* som = (Sound*)cp;
                    som->Play();
                }
                lastMiniLiberado.at(idAlien) = id;
                liberado = true;
                resetPos.at(idAlien) = 1;
                nextMiniLiberado.at(idAlien) = 0;
                InputManager::GetInstance().SetLoadMinions(idAlien);

                cout << "mini id: " << id << " alien id: " << idAlien+1 <<  " loadMini:" << InputManager::GetInstance().GetLoadMinions()->at(idAlien) << endl;
            }
            
            
            if (liberado) {
                // cout << "antes -> mini x: " << associated.box.x << " mini y: " << associated.box.y << endl;
                float x = (alienCenter.lock()->box.x + (alienCenter.lock()->box.w / 2));
                float y = (alienCenter.lock()->box.y + (alienCenter.lock()->box.h / 2));
                //cout << "alienC x: " << x << " alienC y: " << y << endl;
                origin.x = x - associated.box.w / 2;
                origin.y = y - associated.box.h / 2;
            
                bool initPos = false;
                if (xyLinha.x > diametro && allFree.at(idAlien) == 0) { 
                    initPos = true;
                }

                if(!initPos) {
                    associated.box.x = xyLinha.x;
                    associated.box.y = xyLinha.y;
                    // cout << "mini x: " << associated.box.x << " mini y: " << associated.box.y << endl;
                    associated.box.x += origin.x;
                    associated.box.y += origin.y;
                }
                
                
            }
            
        }
        //cout << "size lastMiniLiberado: " << lastMiniLiberado.size() << " nextMiniLiberado: " << nextMiniLiberado.size() << " resetPos: " << resetPos.size() << " allFree: " << allFree.size() << endl << endl;
        if (allFree.at(idAlien) == 1) {
            cout << "mini id: " << id << " alien id: " << idAlien+1 <<  " loadMini:" << InputManager::GetInstance().GetLoadMinions()->at(idAlien) << endl;
            arc = 2;
            ang += - 2;
        } else {
            if (liberado) {
                ang += - arc;
            }
        }
        associated.angleDeg = ang;

        // // cout << " ang: " << ang << endl;

        // // cout << "Id: " << id << " | x: " << associated.box.x << " y: " << associated.box.y << endl << endl;
        // // cout << "Minions Liberados: " << InputManager::GetInstance().GetLoadMinions() << endl;
        
        if (InputManager::GetInstance().GetLoadMinions()->at(idAlien) == numMinions) {
            allFree.at(idAlien) = 1;
        }


        
    } else {
        GameObject* expl = new GameObject();
        Sprite* ex = new Sprite(*expl, "resources/images/miniondeath.png", 4, 0.08, 0.32);
        expl->AddComponent(ex);
        expl->box.x = associated.box.GetCenter().x - ex->GetWidth()/2;
        expl->box.y = associated.box.GetCenter().y - ex->GetHeight()/2;
        Game::GetInstance().GetState().AddObject(expl);
        associated.RequestDelete();
    }
}

void Minion::Render() {

}

bool Minion::Is(string type) {
    string minion = "Minion";
    if (type == minion || Being::Is(type) ){
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
    
    // if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
    //     sourceShoot.x = associated.box.x + associated.box.w/2.0;
    //     sourceShoot.y = associated.box.y + associated.box.h/2.0;
    //     // cout << "boom sourceShoot x: " << sourceShoot.x << " sourceShoot y: " << sourceShoot.y << endl;
    // }
    sourceShoot.x = associated.box.x + associated.box.w/2.0;
    sourceShoot.y = associated.box.y + associated.box.h/2.0;

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
    Bullet* bul = new Bullet(*bullet, angle, speed, damage, maxDistance, false, 3, "resources/images/minionbullet2.png");
    bullet->AddComponent(bul);
    Sound* som = new Sound(*bullet, "resources/sounds/tiro.wav");
    som->Play();
    bullet->AddComponent(som);
    Game::GetInstance().GetState().AddObject(bullet);
    
}

void Minion::NotifyCollision(GameObject& other) {
    if (!other.GetComponent("Being")) {
        Component* cp = other.GetComponent("Bullet");
        if (cp) {
            Bullet* bl = (Bullet*) cp;
            if (bl->targetsPlayer) {
                //cout << "Bateu no Minion: W: " << other.box.w << endl;
            }
        }
        
    }
}