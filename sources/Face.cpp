#include "../headers/Face.h"
#include "../headers/GameObject.h"


void Face::Damage (int damage){
    if (hitpoints <= 0){
        associated.RequestDelete();
    } else {
        hitpoints -= damage;
    }
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