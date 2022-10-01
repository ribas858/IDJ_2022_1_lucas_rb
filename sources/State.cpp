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
    Camera::Follow(alien);
    AddObject(alien);

    

    
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
    music.Play();
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

    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        float PI = 3.14159;
        Vec2 objPos = Vec2(200, 0).Rotate( -PI + PI*(rand() % 1001)/500.0 ).Soma(Vec2
            ( InputManager::GetInstance().GetMouseX() , InputManager::GetInstance().GetMouseY() ));

        // cout << "objPos.x: " << objPos.x << " objPos.y: " << objPos.y << endl;
        // AddObject((int)objPos.x, (int)objPos.y);
    }
    
    if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        cout << "\nmouse X: " << InputManager::GetInstance().GetMouseX() << " | mouse Y: " << InputManager::GetInstance().GetMouseY() << endl;
        // cout << "cam X: " << Camera::pos.x * 64 << " | cam Y: " << Camera::pos.y * 64 << endl;
        
        // bool negCamx, negCamy;

        // float aux, aux2;
        // if (Camera::pos.x < 0) {
        //     negCamx = true;
        //     aux = (Camera::pos.x * -64) + InputManager::GetInstance().GetMouseX();
        // } else {
        //     aux = (Camera::pos.x * 64) - InputManager::GetInstance().GetMouseX();
        //     if (aux < 0) {
        //         aux *= -1;
        //     }
        //     negCamx = false;
        // }
        // if (Camera::pos.y < 0) {
        //     negCamy = true;
        //     aux2 = (Camera::pos.y * -64) + InputManager::GetInstance().GetMouseY();    
        // } else {
        //     negCamy = false;
        //     aux2 = (Camera::pos.y * 64) - InputManager::GetInstance().GetMouseY();
        //     if (aux2 < 0) {
        //         aux2 *= -1;
        //     }
        // }
        
        // cout << "pos tileMap X: " << aux << " | pos tileMap Y: " << aux2 << endl;
        // Camera::pos.x = 512.0/64.0 - aux/64.0;
        // Camera::pos.y = (300.0/64.0 - aux2/64.0);
        
        // cout << "1: pos x: " << Camera::pos.x * 64.0 << " pos y: " << Camera::pos.y * 64.0 << endl;
    
    }

    // InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON);
    // cout << objectArray.size() << endl;

    
    // InputManager::GetInstance().IsKeyDown(SDLK_c);
    // InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON);
    
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
