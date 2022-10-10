#include "../headers/TitleState.h"
#include "../headers/Game.h"
#include "../headers/StageState.h"
#include "../headers/InputManager.h"
#include "../headers/Sprite.h"
#include "../headers/CameraFollower.h"

void TitleState::LoadAssets() {
    GameObject* title = new GameObject();
    Sprite* tl = new Sprite(*title, "resources/images/title.jpg");
    CameraFollower* Cam = new CameraFollower(*title);
    title->AddComponent(Cam);
    title->AddComponent(tl);
    AddObject(title);
}

void TitleState::Start() {
    LoadAssets();
    StartArray();
}


void TitleState::Pause() {

}

void TitleState::Resume() {

}

TitleState::TitleState() {
     cout << "TitleState criado!!" << endl;
}

TitleState::~TitleState() {
   
}

void TitleState::Update(float dt) {

    if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    if(InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        Game::GetInstance().Push(new StageState());
    }

    UpdateArray(dt);

}

void TitleState::Render() {
    RenderArray();
}
