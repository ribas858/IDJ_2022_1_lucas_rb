#include "../headers/StageState.h"
#include "../headers/Sprite.h"

#include "../headers/Vec2.h"

#include "../headers/Sound.h"
#include "../headers/TileMap.h"

#include "../headers/InputManager.h"
#include "../headers/Camera.h"
#include "../headers/CameraFollower.h"
#include "../headers/Alien.h"
#include "../headers/Minion.h"
#include "../headers/PenguinBody.h"
#include "../headers/Collider.h"
#include "Collision.cpp"
#include "../headers/TitleState.h"
#include "../headers/Game.h"
#include "../headers/Text.h"
#include "../headers/GameData.h"
#include "../headers/EndState.h"



void StageState::LoadAssets() {
    Vec2 tileSetTam(64,64);

    backgroundMusic = Music("resources/music/stageState.ogg");

    GameObject* background = new GameObject();
    Sprite* bg = new Sprite(*background, "resources/images/ocean.jpg");
    background->AddComponent(bg);
    CameraFollower* Cam = new CameraFollower(*background);
    background->AddComponent(Cam);
    AddObject(background);

    GameObject* map_obj = new GameObject();
    TileSet* tset = new TileSet(tileSetTam.x, tileSetTam.y, "resources/images/tileset.png");
    TileMap* tmap = new TileMap(*map_obj, "resources/maps/tileMap.txt", tset);
    map_obj->AddComponent(tmap);
    AddObject(map_obj);
    

    for (int i=0; i<3; i++) {
        GameObject* alien = new GameObject();
        srand(i * (rand() % 5000000) * (rand() % 5) );
        alien->box.x = rand() % 1408;
        alien->box.y = rand() % 1280;

        if (alien->box.x > 400 && alien->box.x < 1000) {
            if (alien->box.x > 800 && alien->box.x < 1000) {
                alien->box.x = 1200;
            } else {
                alien->box.x = 0;
            }
        }

        const float MIN_RAND = 0.5, MAX_RAND = 4.5;
        const float range = MAX_RAND - MIN_RAND;
        float timeOffset = range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND;
        Alien* ali = new Alien(*alien, 5, timeOffset);
        alien->AddComponent(ali);
        AddObject(alien);
    }
    Minion::CleanGlobals();

    GameObject* penguin = new GameObject();
    penguin->box.x = 704;
    penguin->box.y = 640;
    PenguinBody* pbody = new PenguinBody(*penguin);
    penguin->AddComponent(pbody);
    Camera::Follow(penguin);
    AddObject(penguin);
    cout << "criou pinguin" << endl;

    GameObject* pontos = new GameObject();
    Sprite* pt = new Sprite(*pontos, "resources/images/pontos.png");
    pontos->AddComponent(pt);
    CameraFollower* Cam5 = new CameraFollower(*pontos);
    pontos->AddComponent(Cam5);
    AddObject(pontos);

    GameObject* pen = new GameObject();
    Sprite* p = new Sprite(*pen, "resources/images/peng_pontos.png");
    pen->AddComponent(p);
    CameraFollower* Cam6 = new CameraFollower(*pen, {15, 6});
    pen->AddComponent(Cam6);
    AddObject(pen);

    GameObject* texto = new GameObject();
    SDL_Color color = InputManager::GetInstance().CreateColor("0eff00");
    Text* tx = new Text(*texto, "resources/font/AGENTORANGE.TTF", 15, Text::TextStyle::BLENDED, "HP: 200", color, 1);
    cout << "id: " << tx->GetId() << endl;
    texto->AddComponent(tx);
    CameraFollower* Cam2 = new CameraFollower(*texto, {80, 35});
    texto->AddComponent(Cam2);
    AddObject(texto);

    GameObject* texto2 = new GameObject();
    SDL_Color color1 = InputManager::GetInstance().CreateColor("ffffff");
    Text* tx1 = new Text(*texto2, "resources/font/AGENTORANGE.TTF", 15, Text::TextStyle::BLENDED, "Pontos: 0", color1, 2);
    cout << "id: " << tx1->GetId() << endl;
    texto2->AddComponent(tx1);
    CameraFollower* Cam3 = new CameraFollower(*texto2, {20, 75});
    texto2->AddComponent(Cam3);
    AddObject(texto2);

    GameObject* mon = new GameObject();
    Sprite* m = new Sprite(*mon, "resources/images/minion.png");
    m->SetScale(0.8, 0.8);
    mon->AddComponent(m);
    CameraFollower* Cam7 = new CameraFollower(*mon, {15, 130});
    mon->AddComponent(Cam7);
    AddObject(mon);

    GameObject* texto3 = new GameObject();
    SDL_Color color2 = InputManager::GetInstance().CreateColor("ffffff");
    Text* tx2 = new Text(*texto3, "resources/font/AGENTORANGE.TTF", 20, Text::TextStyle::BLENDED, "Aliens", color2);
    cout << "id: " << tx2->GetId() << endl;
    texto3->AddComponent(tx2);
    CameraFollower* Cam4 = new CameraFollower(*texto3, {75, 130});
    texto3->AddComponent(Cam4);
    AddObject(texto3);

    GameObject* texto4 = new GameObject();
    SDL_Color color3 = InputManager::GetInstance().CreateColor("ffffff");
    Text* tx3 = new Text(*texto4, "resources/font/AGENTORANGE.TTF", 15, Text::TextStyle::BLENDED, "0", color3, 3);
    cout << "id: " << tx3->GetId() << endl;
    texto4->AddComponent(tx3);
    CameraFollower* Cam8 = new CameraFollower(*texto4, {105, 170});
    texto4->AddComponent(Cam8);
    AddObject(texto4);

    //Text::ClearGlobals();


}

void StageState::Start() {
    LoadAssets();
    StartArray();
    started = true;
    // backgroundMusic.Play();
    cout << "Tudo iniciado.." << endl;
}


void StageState::Pause() {

}

void StageState::Resume() {
    cout << "Resume STAGE STATE" << endl;
    Alien::CleanGlobals();
}

StageState::StageState() {
    cout << "State criado!!" << endl;
}

StageState::~StageState() {
    objectArray.clear();
}

void StageState::Update(float dt) {
    Camera::Update(dt);

    if(InputManager::GetInstance().QuitRequested()) {
        backgroundMusic.~Music(); // Descomentar
        quitRequested = true;
    }
    
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        backgroundMusic.~Music(); // Descomentar
        popRequested = true;
    }

    
    
    UpdateArray(dt);
    ClearObject();

    

    for(int i=0; i<objectArray.size(); i++) {
        Component* cp0 = objectArray[i]->GetComponent("Collider");
        if (cp0) {
            Collider* cold0 = (Collider*)cp0;

            for(int j = i+1; j<objectArray.size(); j++) {
                Component* cp1 = objectArray[j]->GetComponent("Collider");
                if (cp1) {
                    Collider* cold1 = (Collider*)cp1;

                    if ( Collision::IsColliding(cold0->box, cold1->box, (objectArray[i]->angleDeg* PI) / 180, objectArray[j]->angleDeg * PI / 180) ) {
                        //cout << "colidiu meu mano" << endl;
                        //cout << "obj i: " << objectArray[i]->box.w << " obj j: " << objectArray[j]->box.w << endl;
                        objectArray[i]->NotifyCollision(*objectArray[j]);
                        objectArray[j]->NotifyCollision(*objectArray[i]);
                    }
                }
            }
        }
        
    }
    // cout << GameData::alienCount << endl;

    Text* t = GetText(2);
    if (t) {
        t->SetText("Pontos: " + to_string(GameData::pontos));
    }

    if (GameData::alienCount == 0) {
        GameObject* perd = new GameObject();
        Sprite* pd = new Sprite(*perd, "resources/images/gan.png");
        perd->AddComponent(pd);
        CameraFollower* Cam = new CameraFollower(*perd);
        perd->AddComponent(Cam);
        Game::GetInstance().GetCurrentState().AddObject(perd);
        GameData::alienCount = -1;
    }
    else if (GameData::alienCount == -1) {
        mudaState.Update(dt);
        if(mudaState.Get() > 1.6) {
            GameData::alienCount = 0;
            mudaState.Restart();
            GameData::playerVictory = true;
            popRequested = true;
            Game::GetInstance().Push(new EndState());
        }
    } else {
        Text* t = GetText(3);
        if (t) {
            t->SetText(to_string(GameData::alienCount));
        }
    }

    if (!PenguinBody::player) {
        mudaState.Update(dt);
        if(mudaState.Get() > 1.6) {
            mudaState.Restart();
            GameData::playerVictory = false;
            popRequested = true;
            Game::GetInstance().Push(new EndState());
        }
    } else {
        Text* t = GetText(1); 
        if (t) {
            t->SetText("HP: " + to_string(PenguinBody::player->GetHp()));
        }
    }
    
    //cout << endl;

}

void StageState::Render() {
    RenderArray();
}
