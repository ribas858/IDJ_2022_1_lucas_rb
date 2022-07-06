#include "../headers/State.h"

State::State() {
    cout << "State criado!!" << endl;
    music = new Music("sounds/stageState.ogg");
    music->Play();
    quitRequested = false;

    // GameObject* back = new GameObject();
    // bg = new Sprite("images/ocean.jpg");
    // back->AddComponent(bg);
    
    
    //bg = new Sprite("images/ocean.jpg");
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {}

void State::Update(float dt) {
    if(SDL_QuitRequested()) {
        quitRequested = true;
    }
}

void State::Render() {
    //bg->Render();
    
}
