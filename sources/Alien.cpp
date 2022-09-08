#include "../headers/Alien.h"
#include "../headers/Sprite.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"

Vec2 Alien::inicialPos(0,0);
Vec2 Alien::Desloc(0,0);
Vec2 Alien::fimDesloc(0,0);
int Alien::flag = 0;

Alien::Alien(GameObject & associated, int nMinions) : Component(associated) {
    Sprite* alienSprite = new Sprite(associated, "resources/images/alien.png");
    associated.AddComponent(alienSprite);
    associated.box.x = associated.box.x - (associated.box.w / 2);
    associated.box.y =  associated.box.y - (associated.box.h / 2);

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
    cout << "start alien" << endl;
}

void Alien::Update(float dt) {
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        cout << "ATIRA" << endl << endl;
        taskQueue.emplace(Action::ActionType::SHOOT, (float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY());
    }
    if (InputManager::GetInstance().MousePress(RIGHT_MOUSE_BUTTON)) {
        cout << "MOVE:" << endl;
        taskQueue.emplace(Action::ActionType::MOVE, (float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY());
    }
    // cout << "Tamanho fila de acoes: " << taskQueue.size() << endl;
    if (!taskQueue.empty()) {
        if (taskQueue.front().type == Action::ActionType::MOVE) {
            // cout << "MOVE:" << endl;
            
            if (flag == 0) {
                inicialPos.x = associated.box.x;
                inicialPos.y = associated.box.y;
                Desloc.x = taskQueue.front().pos.x - associated.box.x;
                Desloc.y = taskQueue.front().pos.y - associated.box.y;
                flag = 1;
            }
            speed.x = Desloc.x / (1/dt);
            speed.y = Desloc.y / (1/dt);

            // cout << "Speed Y: " << speed.x << " | Speed Y: " << speed.y << endl;

            if (Desloc.x < 0) {
                speed.x *= -1;
                if (fimDesloc.x == 0) {
                    associated.box.x -= speed.x;
                    if (associated.box.x < taskQueue.front().pos.x) {
                        // cout << "x neg -: +1" << endl;
                        fimDesloc.x++;
                    }
                }
            } else if (Desloc.x > 0) {
                if (fimDesloc.x == 0) {
                    associated.box.x += speed.x;
                    if (associated.box.x > taskQueue.front().pos.x) {
                        // cout << "x posit : +1" << endl;
                        fimDesloc.x++;
                    }
                }
            }
            if (Desloc.y < 0) {
                speed.y *= -1;
                if (fimDesloc.y == 0) {
                    associated.box.y -= speed.y;
                    if (associated.box.y < taskQueue.front().pos.y) {
                        // cout << "y neg -: +1" << endl;
                        fimDesloc.y++;
                    }
                }
            } else if (Desloc.y > 0) {
                if (fimDesloc.y == 0) {
                    associated.box.y += speed.y;
                    if (associated.box.y > taskQueue.front().pos.y) {
                        // cout << "y posit : +1" << endl;
                        fimDesloc.y++;
                    }
                }
            }

            
            if (fimDesloc.x == 1 && fimDesloc.y == 1) {
                cout << "Fim Desloc. X: " << fimDesloc.x << " | Fim Desloc. y: " << fimDesloc.y << endl;
                printf("Pos X0: %.6f | Pos Y0: %.6f\n", inicialPos.x, inicialPos.y);
                printf("Pos X: %.6f | Pos Y: %.6f\n", taskQueue.front().pos.x, taskQueue.front().pos.y);
                
                fimDesloc.x = 0;
                fimDesloc.y = 0;
                flag = 0;
                taskQueue.pop();
                cout << "Tamanho fila de acoes: " << taskQueue.size() << endl << endl;
            }
            // associated.box.x = taskQueue.front().pos.x;
            // associated.box.y = taskQueue.front().pos.y;
            // // 
        }
        else if (taskQueue.front().type == Action::ActionType::SHOOT) {
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
    return false; // compile test
}