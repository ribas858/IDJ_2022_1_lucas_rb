#include "../headers/Alien.h"
#include "../headers/Sprite.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"
#include "../headers/Minion.h"
#include "../headers/Game.h"
#include "../headers/State.h"
#include "../headers/Sound.h"

Vec2 Alien::inicialPos(0,0);
Vec2 Alien::desloc(0,0);
Vec2 Alien::fimDesloc(0,0);
int Alien::flag = 0;

// State& state = Game::GetInstance().GetState();

Alien::Alien(GameObject & associated, int nMinions) : Component(associated), nMinions(nMinions) {

    Sprite* alienSprite = new Sprite(associated, "resources/images/alien.png");
    // alienSprite->SetScale(2,2);
    associated.AddComponent(alienSprite);
    Sound* som = new Sound(associated, "resources/sounds/mini.wav");
    associated.AddComponent(som);

    associated.box.x = associated.box.x - (associated.box.w / 2);
    associated.box.y =  associated.box.y - (associated.box.h / 2);


    cout << "alien w: " << associated.box.w << " alien h: " << associated.box.h << endl;
    cout << "alien x: " << associated.box.x << " alien y: " << associated.box.y << endl;
    speed.x = 0;
    speed.y = 0;
}

Alien::~Alien() {
    for (int i = 0; i < minionArray.size(); i++) {
        minionArray[i].reset();
    }
    minionArray.clear();
}

void Alien::Start() {
    // cout << "start alien" << endl;

    for (int i = 1; i <= nMinions; i++) {
        GameObject* minion = new GameObject();
        const float MIN_RAND = 1.0, MAX_RAND = 1.5;
        const float range = MAX_RAND - MIN_RAND;
        // cout << range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND << endl;

        float scale = range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND;
        Vec2 s(scale,scale);
        //Vec2 s(1,1);
        
        if (i == 1) {
            Minion* mini = new Minion(*minion, Game::GetInstance().GetState().GetObjectPtr(&associated), 4, true, i, nMinions, s);
            minion->AddComponent(mini);
        } else {
            Minion* mini = new Minion(*minion, Game::GetInstance().GetState().GetObjectPtr(&associated), 4, false, i, nMinions, s);
            minion->AddComponent(mini);
        }

        minionArray.push_back(Game::GetInstance().GetState().AddObject(minion));
        
    }

}

void Alien::Update(float dt) {

    //cout << "alien x: " << associated.box.x << " alien y: " << associated.box.y << endl;

    associated.angleDeg++;
    if (associated.angleDeg == 360) {
        associated.angleDeg = 0;
    }

    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        cout << "\nATIRA" << endl;
        taskQueue.emplace(Action::ActionType::SHOOT, (float)InputManager::GetInstance().GetMouseX() + Camera::pos.x, (float)InputManager::GetInstance().GetMouseY() + Camera::pos.y);
    }
    if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
        cout << "\nMOVE ===================================================" << endl;
        taskQueue.emplace(Action::ActionType::MOVE, (float)InputManager::GetInstance().GetMouseX() + Camera::pos.x, (float)InputManager::GetInstance().GetMouseY() + Camera::pos.y);
        //taskQueue.emplace(Action::ActionType::MOVE, 700.0, 400.0);
    }
    // cout << "Tamanho fila de acoes: " << taskQueue.size() << endl;
    if (!taskQueue.empty()) {
        if (taskQueue.front().type == Action::ActionType::MOVE && InputManager::GetInstance().GetLoadMinions() == minionArray.size()) {
            // cout << "MOVE:" << endl;
            
            if (flag == 0) {
                inicialPos.x = associated.box.x;
                inicialPos.y = associated.box.y;
                desloc.x = taskQueue.front().pos.x - (associated.box.x + associated.box.w/2);
                desloc.y = taskQueue.front().pos.y - (associated.box.y + associated.box.h/2);
                flag = 1;
            }
            speed.x = desloc.x / (1/dt);
            speed.y = desloc.y / (1/dt);
            

            if (desloc.x < 0) {
                
                if (fimDesloc.x == 0) {
                    associated.box.x += speed.x;
                    if (associated.box.x  + associated.box.w/2 < taskQueue.front().pos.x) {
                        // cout << "x neg -: +1" << endl;
                        fimDesloc.x++;
                    }
                }
            } else if (desloc.x > 0) {
                if (fimDesloc.x == 0) {
                    associated.box.x += speed.x;
                    if (associated.box.x  + associated.box.w/2 > taskQueue.front().pos.x) {
                        // cout << "x posit : +1" << endl;
                        fimDesloc.x++;
                    } 
                }
            }
            if (desloc.y < 0) {
                if (fimDesloc.y == 0) {
                    associated.box.y += speed.y;
                    if (associated.box.y  + associated.box.h/2 < taskQueue.front().pos.y) {
                        // cout << "y neg -: +1" << endl;
                        fimDesloc.y++;
                    }
                }
            } else if (desloc.y > 0) {
                if (fimDesloc.y == 0) {
                    associated.box.y += speed.y;
                    if (associated.box.y  + associated.box.h/2 > taskQueue.front().pos.y) {
                        // cout << "y posit : +1" << endl;
                        fimDesloc.y++;
                    }
                }
            }
            //cout << "x: " << associated.box.x << " y: " << associated.box.y << endl;
            //printf("limite X: %.6f | limite Y: %.6f\n", taskQueue.front().pos.x, taskQueue.front().pos.y);
            
            if (fimDesloc.x == 1 && fimDesloc.y == 1) {
                cout << "\nFim Desloc. X: " << fimDesloc.x << " | Fim Desloc. y: " << fimDesloc.y << endl;
                printf("Pos X0: %.6f | Pos Y0: %.6f\n", inicialPos.x, inicialPos.y);
                printf("Pos X: %.6f | Pos Y: %.6f\n", taskQueue.front().pos.x, taskQueue.front().pos.y);
                printf("Cam X: %.6f | Cam Y: %.6f\n", Camera::pos.x, Camera::pos.y);
                
                fimDesloc.x = 0;
                fimDesloc.y = 0;
                flag = 0;
                taskQueue.pop();
                speed.x = 0;
                speed.y = 0;
                cout << "Tamanho fila de acoes: " << taskQueue.size() << endl << endl;
            }
            // associated.box.x = taskQueue.front().pos.x;
            // associated.box.y = taskQueue.front().pos.y;
            // // 
        }
        else if (taskQueue.front().type == Action::ActionType::SHOOT) {
            int id = 0;

            float deslocEscalar = 0;
            float min = 99999999;
            for (int i=0; i<minionArray.size(); i++) {
                float x = taskQueue.front().pos.x - minionArray[i].lock()->box.x;
                float y = taskQueue.front().pos.y - minionArray[i].lock()->box.y;
                deslocEscalar = sqrt(pow(x, 2) + pow(y, 2));
                if (deslocEscalar < min) {
                    min = deslocEscalar;
                    id = i;
                }
            }
            cout << "Minion Mais Perto: " << id << " Distancia: " << min << endl;

            if(auto mini = minionArray[id].lock()) {
                Minion* minion = (Minion*) mini->GetComponent("Minion");
                
                if(minion) {
                    minion->Shoot(taskQueue.front().pos);
                    
                }
            }
            
            taskQueue.pop();
        }

        if (hp <= 0) {
            associated.RequestDelete();
        }
        
    }
    
}

void Alien::Render() {

}

bool Alien::Is(string type) {
    string alien = "Alien";
    if (type == alien){
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