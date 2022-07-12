#include "../headers/Face.h"
#include "../headers/Sound.h"
#include "../headers/Game.h"

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage (int damage){
    hitpoints -= damage;
    if (hitpoints <= 0){
        Component* cp = associated.GetComponent("Sound"); 
        if (cp) {
            Sound* som = (Sound*)cp;
            som->Play();
            cout << "BOOMMMMM..." << endl;
        }
        
        SDL_RenderClear(Game::GetInstance().GetRenderer());
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