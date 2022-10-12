#include "../headers/TitleState.h"
#include "../headers/Game.h"
#include "../headers/StageState.h"
#include "../headers/InputManager.h"
#include "../headers/Sprite.h"
#include "../headers/CameraFollower.h"
#include "../headers/Text.h"
#include "../headers/Camera.h"

void TitleState::LoadAssets() {

    GameObject* title = new GameObject();
    Sprite* tl = new Sprite(*title, "resources/images/title.jpg");
    CameraFollower* Cam = new CameraFollower(*title);
    title->AddComponent(Cam);
    title->AddComponent(tl);
    AddObject(title);

    GameObject* texto = new GameObject();
    texto->box.x = 512;
    texto->box.y = 410;
    SDL_Color color = InputManager::GetInstance().CreateColor("ffffff");
    Text* tx = new Text(*texto, "resources/font/Call me maybe.ttf", 35, Text::TextStyle::BLENDED, "Pressione SPACE para jogar", color, 0.8);
    texto->AddComponent(tx);
    AddObject(texto);

    GameObject* spaceKey = new GameObject();
    Sprite* sp = new Sprite(*spaceKey, "resources/images/space.png", 6, 0.07);
    sp->SetScale(0.5, 0.5);
    spaceKey->box.x = spaceKey->box.PosCenter().x + 512;
    spaceKey->box.y = spaceKey->box.PosCenter().y + 500;
    spaceKey->AddComponent(sp);
    AddObject(spaceKey);


    
}

void TitleState::Start() {
    cout << "\nSTART TitleState" << endl;
    LoadAssets();
    StartArray();
}


void TitleState::Pause() {

}

void TitleState::Resume() {
    cout << "RESUME TitleState" << endl;
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

TitleState::TitleState() {

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
