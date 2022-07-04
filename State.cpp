#include "State.h"
#include "Music.h"
#include "Game.h"


State::State() {
    cout << "State criado!!" << endl;
    music = new Music("stageState.ogg");
    music->Play();
    quitRequested = false;
    bg = new Sprite("ocean.jpg");
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
