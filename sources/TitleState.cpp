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
    texto->box.y = 400;
    SDL_Color color = InputManager::GetInstance().CreateColor("f58b3e");
    Text* tx = new Text(*texto, "resources/font/Call me maybe.ttf", 35, Text::TextStyle::BLENDED, "Pressione SPACE para continuar...", color);
    texto->AddComponent(tx);
    AddObject(texto);


    
}

void TitleState::Start() {
    cout << "\nstart TITLE STATE" << endl;
    LoadAssets();
    StartArray();
}


void TitleState::Pause() {

}

void TitleState::Resume() {
    cout << "resume title state" << endl;
    Camera::pos.x = 0;
    Camera::pos.y = 0;
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
    texto.Update(dt);

    for (int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->GetComponent("Text")) {
            auto tx = (Text*)objectArray[i]->GetComponent("Text");
            if(texto.Get() > 0.8) {
                tx->SetAtivar(false);
            } else {
                tx->SetAtivar(true);
            }
            if(texto.Get() > 1.2) {
                texto.Restart();
            }
            
        }
    }

}

void TitleState::Render() {
    RenderArray();
}
