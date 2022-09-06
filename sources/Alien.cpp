#include "../headers/Alien.h"
#include "../headers/Sprite.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"

Vec2 Alien::posD(0,0);
Vec2 Alien::flagDs(0,0);
int Alien::flagSpeed = 0;

Alien::Alien(GameObject & associated, int nMinions) : Component(associated) {
    Sprite* alienSprite = new Sprite(associated, "resources/images/alien.png");
    associated.AddComponent(alienSprite);
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
            
            if (flagSpeed == 0) {
                posD.x = taskQueue.front().pos.x - associated.box.x;
                posD.y = taskQueue.front().pos.y - associated.box.y;
                flagSpeed = 1;
            }
            speed.x = posD.x / (1/dt);
            speed.y = posD.y / (1/dt);

            // printf("Pos X0: %.6f | Pos Y0: %.6f\n", associated.box.x, associated.box.y);
            // cout << "Speed Y: " << speed.x << " | Speed Y: " << speed.y << endl;

            if (posD.x < 0) {
                speed.x *= -1;
                if (flagDs.x == 0) {
                    associated.box.x -= speed.x;
                    if (associated.box.x < taskQueue.front().pos.x) {
                        // cout << "x neg -: +1" << endl;
                        flagDs.x++;
                    }
                }
            } else if (posD.x > 0) {
                if (flagDs.x == 0) {
                    associated.box.x += speed.x;
                    if (associated.box.x > taskQueue.front().pos.x) {
                        // cout << "x posit : +1" << endl;
                        flagDs.x++;
                    }
                }
            }
            if (posD.y < 0) {
                speed.y *= -1;
                if (flagDs.y == 0) {
                    associated.box.y -= speed.y;
                    if (associated.box.y < taskQueue.front().pos.y) {
                        // cout << "y neg -: +1" << endl;
                        flagDs.y++;
                    }
                }
            } else if (posD.y > 0) {
                if (flagDs.y == 0) {
                    associated.box.y += speed.y;
                    if (associated.box.y > taskQueue.front().pos.y) {
                        // cout << "y posit : +1" << endl;
                        flagDs.y++;
                    }
                }
            }

            
            if (flagDs.x == 1 && flagDs.y == 1) {
                cout << "Fim Desloc. X: " << flagDs.x << " | Fim Desloc. y: " << flagDs.y << endl;
                printf("Pos X: %.6f | Pos Y: %.6f\n", taskQueue.front().pos.x, taskQueue.front().pos.y);
                
                flagDs.x = 0;
                flagDs.y = 0;
                flagSpeed = 0;
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
        
    }
    
}

void Alien::Render() {

}

bool Alien::Is(string type) {
    return false; // compile test
}