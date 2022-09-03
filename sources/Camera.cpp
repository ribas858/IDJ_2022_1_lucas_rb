#include "../headers/Camera.h"
#include "../headers/InputManager.h"

GameObject* Camera::focus = nullptr;

Vec2 Camera::pos(0,0);
Vec2 Camera::speed(0,0);
Vec2 Camera::tileSetTam(0,0);
Vec2 Camera::flag(0,0);
Vec2 Camera::mouseAcc(0,0);
Vec2 Camera::tela(0,0);

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    speed.x = dt * 2;
    speed.y = dt * 2;

    if (focus) {
        pos.x = 0;
        pos.y = 0;
    }
    else if (!focus) {
        //////////////////////////////////////////////////////////////// RELEASE
        if(InputManager::GetInstance().KeyRelease(LEFT_ARROW_KEY)) {
            // cout << "soltou man" << endl;
            flag.x = 0;
        }
        if(InputManager::GetInstance().KeyRelease(RIGHT_ARROW_KEY)) {
            // cout << "soltou man" << endl;
            flag.x = 0;
        }
        if(InputManager::GetInstance().KeyRelease(UP_ARROW_KEY)) {
            // cout << "soltou man" << endl;
            flag.y = 0;
        }
        if(InputManager::GetInstance().KeyRelease(DOWN_ARROW_KEY)) {
            // cout << "soltou man" << endl;
            flag.y = 0;
        }

        //////////////////////////////////////////////////////////////// IS DOWN
        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
            flag.x = 1;
            // cout << "esq" << endl;
            pos.x += speed.x;
            // cout << "speed x: " << speed.x << endl;
            
        }
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            flag.x = -1;
            // cout << "dir" << endl;
            pos.x -= speed.x;
            // cout << "speed x: " << speed.x << endl;
        }
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
            flag.y = 1;
            // cout << "cima" << endl;
            pos.y += speed.y;
            // cout << "speed y: " << speed.y << endl;
        }
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
            flag.y = -1;
            // cout << "baixo" << endl;
            pos.y -= speed.y;
            // cout << "speed y: " << speed.y << endl;
        }
    }
    
}