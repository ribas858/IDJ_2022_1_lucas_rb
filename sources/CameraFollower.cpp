#include "../headers/CameraFollower.h"
#include "../headers/Camera.h"
#include "../headers/InputManager.h"

CameraFollower::CameraFollower(GameObject& associated) : Component(associated) {
    
}

void CameraFollower::Update(float dt) {
    associated.box.x = Camera::pos.x;
    associated.box.y = Camera::pos.y;
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
    cout << "start camera" << endl;
}