#include "../headers/CameraFollower.h"
#include "../headers/Camera.h"
#include "../headers/InputManager.h"

CameraFollower::CameraFollower(GameObject& associated) : Component(associated) {
    
}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
    // if (InputManager::GetInstance().IsKeyDown(SDLK_c)) {
   // cout  << " Update: pos x: " << associated.box.x << " pos y: " << associated.box.x << endl << endl;
    // }
    
}

void CameraFollower::Render() {
    
}

bool CameraFollower::Is(string type) {
    string CamF = "CameraFollower";
    if (type == CamF){
        return true;
    } else {
        return false;
    }
}

void CameraFollower::Start() {
    cout << "start not camera" << endl;
}