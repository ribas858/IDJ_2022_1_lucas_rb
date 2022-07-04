#include "../headers/State.h"
#include "../headers/Music.h"
#include "../headers/Game.h"


State::State() {
    cout << "State criado!!" << endl;
    music = new Music("sounds/stageState.ogg");
    music->Play();
    quitRequested = false;
    bg = new Sprite("images/ocean.jpg");
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
    bg->Render(0, 0);
}
