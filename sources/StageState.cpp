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
    

    GameObject* alien = new GameObject();
    alien->box.x = 512;
    alien->box.y = 300;
    Alien* ali = new Alien(*alien, 5);
    alien->AddComponent(ali);
    //Camera::Follow(alien);
    AddObject(alien);

    GameObject* a2 = new GameObject();
    a2->box.x = 200;
    a2->box.y = 300;
    Alien* al2 = new Alien(*a2, 5);
    a2->AddComponent(al2);
    //Camera::Follow(alien2);
    AddObject(a2);

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
    
    //cout << endl;

}

void StageState::Render() {
    RenderArray();
}
