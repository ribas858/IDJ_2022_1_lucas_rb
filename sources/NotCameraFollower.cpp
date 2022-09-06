#include "../headers/NotCameraFollower.h"
#include "../headers/Camera.h"

NotCameraFollower::NotCameraFollower(GameObject& go) : Component(go) {

}

void NotCameraFollower::Update(float dt) {
    
}

void NotCameraFollower::Render() {
    
}

bool NotCameraFollower::Is(string type) {
    string CamF = "NotCameraFollower";
    if (type == CamF){
        return true;
    } else {
        return false;
    }
}

void NotCameraFollower::Start() {
    cout << "start not camera" << endl;
}