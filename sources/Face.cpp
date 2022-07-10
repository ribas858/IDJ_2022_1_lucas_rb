#include "../headers/Face.h"

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage (int damage){
    hitpoints -= damage;
    if (hitpoints <= 0){
        cout << "Chama RequesteDelete" << endl;
        associated.RequestDelete();
    }
    cout << "Hitpoints: " << hitpoints << endl;
}

void Face::Update(float dt) {}

void Face::Render() {}

bool Face::Is(string type) {
    string face = "Face";
    if (type == face){
        return true;
    } else {
        return false;
    }
}