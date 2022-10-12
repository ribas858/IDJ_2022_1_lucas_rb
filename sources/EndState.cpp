#include "../headers/EndState.h"
#include "../headers/Game.h"
#include "../headers/StageState.h"
#include "../headers/InputManager.h"
#include "../headers/Sprite.h"
#include "../headers/CameraFollower.h"
#include "../headers/Text.h"
#include "../headers/Camera.h"
#include "../headers/GameData.h"

void EndState::LoadAssets() {

    if (GameData::playerVictory) {
        GameObject* end = new GameObject();
        Sprite* ed = new Sprite(*end, "resources/images/win.jpg");
        CameraFollower* Cam = new CameraFollower(*end);
        end->AddComponent(Cam);
        end->AddComponent(ed);
        AddObject(end);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        GameObject* texto = new GameObject();
        SDL_Color color = InputManager::GetInstance().CreateColor("ffffff");
        Text* tx = new Text(*texto, "resources/font/Call me maybe.ttf", 20, Text::TextStyle::BLENDED, "Jogar Novamente", color);
        texto->box.x = 102;
        texto->box.y = 330;
        texto->AddComponent(tx);
        AddObject(texto);

        GameObject* spaceKey = new GameObject();
        Sprite* sp = new Sprite(*spaceKey, "resources/images/space.png", 6, 0.07);
        sp->SetScale(0.5, 0.5);
        spaceKey->box.x = 114;
        spaceKey->box.y = spaceKey->box.PosCenter().y + 400;
        spaceKey->AddComponent(sp);
        AddObject(spaceKey);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        GameObject* texto2 = new GameObject();
        SDL_Color color2 = InputManager::GetInstance().CreateColor("ffffff");
        Text* tx2 = new Text(*texto2, "resources/font/Call me maybe.ttf", 20, Text::TextStyle::BLENDED, "Sair do Jogo", color);
        texto2->box.x = 896 - texto2->box.w;
        texto2->box.y = 330;
        texto2->AddComponent(tx2);
        AddObject(texto2);

        GameObject* escKey = new GameObject();
        Sprite* esc = new Sprite(*escKey, "resources/images/esc.png", 6, 0.07);
        esc->SetScale(0.5, 0.5);
        escKey->box.x = 910 - escKey->box.w;
        escKey->box.y = escKey->box.PosCenter().y + 400;
        escKey->AddComponent(esc);
        AddObject(escKey);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        GameObject* texto3 = new GameObject();
        SDL_Color color3 = InputManager::GetInstance().CreateColor("ffffff");
        Text* tx3 = new Text(*texto3, "resources/font/BebasNeue.ttf", 25, Text::TextStyle::BLENDED, "Pontos:", color3);
        texto3->box.x = 512 - texto3->box.w;
        texto3->box.y = 365 - texto3->box.h/2;
        texto3->AddComponent(tx3);
        AddObject(texto3);

        GameObject* texto4 = new GameObject();
        SDL_Color color4 = InputManager::GetInstance().CreateColor("21ff0e");
        Text* tx4 = new Text(*texto4, "resources/font/BebasNeue.ttf", 28, Text::TextStyle::BLENDED, to_string(GameData::pontos), color4, 1);
        texto4->box.x = 512 + texto4->box.w;
        texto4->box.y = 365 - texto4->box.h/2;
        texto4->AddComponent(tx4);
        AddObject(texto4);

        GameData::pontos = 0;

    } else {
        GameObject* end = new GameObject();
        Sprite* ed = new Sprite(*end, "resources/images/lose.jpg");
        CameraFollower* Cam = new CameraFollower(*end);
        end->AddComponent(Cam);
        end->AddComponent(ed);
        AddObject(end);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        GameObject* texto = new GameObject();
        SDL_Color color = InputManager::GetInstance().CreateColor("ffffff");
        Text* tx = new Text(*texto, "resources/font/Call me maybe.ttf", 20, Text::TextStyle::BLENDED, "Jogar Novamente", color);
        texto->box.x = 102;
        texto->box.y = 200;
        texto->AddComponent(tx);
        AddObject(texto);

        GameObject* spaceKey = new GameObject();
        Sprite* sp = new Sprite(*spaceKey, "resources/images/space.png", 6, 0.07);
        sp->SetScale(0.5, 0.5);
        spaceKey->box.x = 114;
        spaceKey->box.y = spaceKey->box.PosCenter().y + 270;
        spaceKey->AddComponent(sp);
        AddObject(spaceKey);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        GameObject* texto2 = new GameObject();
        SDL_Color color2 = InputManager::GetInstance().CreateColor("ffffff");
        Text* tx2 = new Text(*texto2, "resources/font/Call me maybe.ttf", 20, Text::TextStyle::BLENDED, "Sair do Jogo", color);
        texto2->box.x = 896 - texto2->box.w;
        texto2->box.y = 200;
        texto2->AddComponent(tx2);
        AddObject(texto2);

        GameObject* escKey = new GameObject();
        Sprite* esc = new Sprite(*escKey, "resources/images/esc.png", 6, 0.07);
        esc->SetScale(0.5, 0.5);
        escKey->box.x = 910 - escKey->box.w;
        escKey->box.y = escKey->box.PosCenter().y + 270;
        escKey->AddComponent(esc);
        AddObject(escKey);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         GameObject* texto3 = new GameObject();
        SDL_Color color3 = InputManager::GetInstance().CreateColor("000000");
        Text* tx3 = new Text(*texto3, "resources/font/BebasNeue.ttf", 25, Text::TextStyle::BLENDED, "Pontos:", color3);
        texto3->box.x = 512 - texto3->box.w;
        texto3->box.y = 266 - texto3->box.h/2;
        texto3->AddComponent(tx3);
        AddObject(texto3);

        GameObject* texto4 = new GameObject();
        SDL_Color color4 = InputManager::GetInstance().CreateColor("d00000");
        Text* tx4 = new Text(*texto4, "resources/font/BebasNeue.ttf", 28, Text::TextStyle::BLENDED, to_string(GameData::pontos), color4, 1);
        texto4->box.x = 512 + texto4->box.w;
        texto4->box.y = 266 - texto4->box.h/2;
        texto4->AddComponent(tx4);
        AddObject(texto4);

        GameData::pontos = 0;
        
    }

   
    
}

void EndState::Start() {
    cout << "\nstart EndState" << endl;
    LoadAssets();
    StartArray();
}


void EndState::Pause() {

}

void EndState::Resume() {
    cout << "resume EndState" << endl;
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

EndState::EndState() {
     cout << "EndState criado!!" << endl;
}

EndState::~EndState() {
   
}

void EndState::Update(float dt) {
    UpdateArray(dt);

    if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        quitRequested = true;
    }

    if(InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        popRequested = true;
        Game::GetInstance().Push(new StageState());
    }


}

void EndState::Render() {
    RenderArray();
}
