#include "../headers/State.h"
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



void State::LoadAssets() {
    Vec2 tileSetTam(64,64);

    music = Music("resources/music/stageState.ogg");

    GameObject* background = new GameObject();
    bg = new Sprite(*background, "resources/images/ocean.jpg");
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

void State::Start() {
    LoadAssets();
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
    //music.Play();
    cout << "Tudo iniciado.." << endl;
}

State::State() : started(false) {
    quitRequested = false;
    cout << "State criado!!" << endl;
}

State::~State() {
    objectArray.clear();
}

bool State::QuitRequested() {
    return quitRequested;
}


void State::Update(float dt) {
    if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(ESCAPE_KEY)) {
        music.~Music(); // Descomentar
        quitRequested = true;
    }

    
    Camera::Update(dt);

    for(int i=0; i<objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    
    for(int i=0; i<objectArray.size(); i++) {
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            // cout << "limpa no objectArray" << endl << endl;
        }
    }

    for(int i=0; i<objectArray.size(); i++) {
        Component* cp0 = objectArray[i]->GetComponent("Collider");
        if (cp0) {
            Collider* cold0 = (Collider*)cp0;

            for(int j = i+1; j<objectArray.size(); j++) {
                Component* cp1 = objectArray[j]->GetComponent("Collider");
                if (cp1) {
                    Collider* cold1 = (Collider*)cp1;

                    if ( Collision::IsColliding(cold0->box, cold1->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg) ) {
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

void State::Render() {
    for (vector<shared_ptr<GameObject>>::iterator ob = objectArray.begin(); ob != objectArray.end(); ob++) {
        (*ob)->Render();
    }
}



weak_ptr<GameObject> State::AddObject(GameObject* go) {
   
    shared_ptr<GameObject> goShared(go);

    objectArray.push_back(goShared);

    if (started) {
        // cout << "State ja foi carregado" << endl;
        goShared->Start();
        weak_ptr<GameObject> gobWeak(goShared);
        return gobWeak;
    }
    weak_ptr<GameObject> gobWeak(goShared);
    return gobWeak;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    // cout << "get weak " << go->box.x << " " << objectArray.empty() << endl;
    for(int i=0; i<objectArray.size(); i++) {
        if (objectArray[i].get() == go) {
            weak_ptr<GameObject> weakPtrReturn(objectArray[i]);
            return weakPtrReturn;
        }
    }
    weak_ptr<GameObject> weakPtrReturn;
    return weakPtrReturn;
}


vector<shared_ptr<GameObject>>& State::GetObjArr() {
    return objectArray;
}
