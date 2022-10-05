#include "../headers/Camera.h"
#include "../headers/InputManager.h"
#include "../headers/Alien.h"

GameObject* Camera::focus = nullptr;

Vec2 Camera::pos(0,0);
Vec2 Camera::speed(0,0);
Vec2 Camera::focusAux(0,0);



void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
    focusAux.x = focus->box.x;
    focusAux.y = focus->box.y;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    speed.x = 100 * dt;
    speed.y = 100 * dt;

    if (focus) {

        pos.x = focus->box.x - 512.0 + focus->box.w/2;
        pos.y = focus->box.y - 300.0 + focus->box.h/2;
        
    }
    else if (!focus) {
        //////////////////////////////////////////////////////////////// IS DOWN
        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
            pos.x -= speed.x;  
        }
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            pos.x += speed.x;
        }
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
            pos.y -= speed.y;
        }
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
            pos.y += speed.y;
        }
    }
    
}