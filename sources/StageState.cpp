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
    

    for (int i=0; i<5; i++) {
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

        // cout << alien->box.x << " " << alien->box.y << " time: " << timeOffset << endl;
        Alien* ali = new Alien(*alien, 5, timeOffset);
        alien->AddComponent(ali);
        //Camera::Follow(alien);
        AddObject(alien);
    }

    

    // GameObject* a2 = new GameObject();
    // a2->box.x = 200;
    // a2->box.y = 300;
    // Alien* al2 = new Alien(*a2, 5);
    // a2->AddComponent(al2);
    // //Camera::Follow(alien2);
    // AddObject(a2);

    Minion::CleanGlobals();

    GameObject* penguin = new GameObject();
    penguin->box.x = 704;
    penguin->box.y = 640;
    PenguinBody* pbody = new PenguinBody(*penguin);
    penguin->AddComponent(pbody);
    Camera::Follow(penguin);
    AddObject(penguin);
    cout << "criou pinguin" << endl; 



    // GameObject* sonic = new GameObject();
    // Sprite* snc = new Sprite(*sonic, "resources/images/sonic.png", 6, 0.05);
    // cout << " width antes: " << snc->GetWidth() << " " << snc->GetHeight() << endl;
    // snc->SetScale(5, 5);
    // sonic->AddComponent(snc);
    // Collider* cold = new Collider(*sonic);
    // sonic->AddComponent(cold);
    // //sonic->box.x = -100;
    // //Camera::Follow(sonic);
    // AddObject(sonic);


    
    // GameObject* ponto = new GameObject();
    // Sprite* pt = new Sprite(*ponto, "resources/images/minion_pt.png");
    // ponto->AddComponent(pt);
    // ponto->box.x = 512 - 10;
    // ponto->box.y = 300 - 10;
    // shared_ptr<GameObject> ptShared(ponto);
    // objectArray.push_back(ptShared);

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
    if(InputManager::GetInstance().QuitRequested()) {
        backgroundMusic.~Music(); // Descomentar
        quitRequested = true;
    }
    
    if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        backgroundMusic.~Music(); // Descomentar
        popRequested = true;
    }

    
    Camera::Update(dt);
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
    if (GameData::alienCount == 0) {
        GameData::playerVictory = true;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
    }
    if (!PenguinBody::player) {
        GameData::playerVictory = false;
        popRequested = true;
        Game::GetInstance().Push(new EndState());
    }
    
    //cout << endl;

}

void StageState::Render() {
    RenderArray();
}
