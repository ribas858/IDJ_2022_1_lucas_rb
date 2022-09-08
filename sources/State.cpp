#include "../headers/State.h"
#include "../headers/Sprite.h"

#include "../headers/Vec2.h"

#include "../headers/Sound.h"
#include "../headers/TileMap.h"

#include "../headers/InputManager.h"
#include "../headers/Camera.h"
#include "../headers/NotCameraFollower.h"
#include "../headers/Alien.h"
#include "../headers/Minion.h"



void State::LoadAssets() {
    Vec2 tileSetTam(64,64);
    Camera::tileSetTam = tileSetTam;

    music = Music("resources/music/stageState.ogg");

    GameObject* background = new GameObject();
    bg = new Sprite(*background, "resources/images/ocean.jpg");
    background->AddComponent(bg);
    NotCameraFollower* notCam = new NotCameraFollower(*background);
    background->AddComponent(notCam);
    shared_ptr<GameObject> backShared(background);
    objectArray.push_back(backShared);
    

    GameObject* map_obj = new GameObject();
    TileSet* tset = new TileSet(tileSetTam.x, tileSetTam.y, "resources/images/tileset.png");
    TileMap* tmap = new TileMap(*map_obj, "resources/maps/tileMap.txt", tset);
    map_obj->AddComponent(tmap);
    
    shared_ptr<GameObject> mapShared(map_obj);
    objectArray.push_back(mapShared);

    GameObject* alien = new GameObject();
    alien->box.x = 439;
    alien->box.y = 218.5;
    Alien* ali = new Alien(*alien, 1);
    alien->AddComponent(ali);
    shared_ptr<GameObject> aliShared(alien);
    weak_ptr<GameObject> aliWeak(aliShared);

    GameObject* minion = new GameObject();
    Minion* mini = new Minion(*minion, aliWeak);
    minion->AddComponent(mini);
    shared_ptr<GameObject> miniShared(minion);

    objectArray.push_back(aliShared);
    objectArray.push_back(miniShared);

    GameObject* ponto = new GameObject();
    Sprite* pt = new Sprite(*ponto, "resources/images/minion.png");
    ponto->AddComponent(pt);
    ponto->box.x = 300;
    ponto->box.y = 300;
    shared_ptr<GameObject> ptShared(ponto);
    objectArray.push_back(ptShared);

}

void State::Start() {
    LoadAssets();
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
    started = true;
    // music.Play();
    cout << "Start meu consagrado" << endl;
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
    
    // InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON);
    // InputManager::GetInstance().MouseRelease(LEFT_MOUSE_BUTTON);
    // cout << objectArray.size() << endl;

    
    // InputManager::GetInstance().IsKeyDown(SDLK_c);
    // InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON);
    
    for(int i=0; i<objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
    
    for(int i=0; i<objectArray.size(); i++) {
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            // cout << "limpa no objectArray" << endl << endl;
        }
    }

    Camera::Update(dt);
}

void State::Render() {
    for (vector<shared_ptr<GameObject>>::iterator ob = objectArray.begin(); ob != objectArray.end(); ob++) {
        (*ob)->Render();
    }
}



weak_ptr<GameObject> State::AddObject(GameObject* go) {
    int mouseX, mouseY;
    GameObject* gob = new GameObject();
    Sprite* penguin = new Sprite(*gob, "resources/images/penguinface.png");
    
    Sound* boom = new Sound(*gob, "resources/sounds/boom.wav");
    // Face* logik = new Face(*gob);
    NotCameraFollower* notCam = new NotCameraFollower(*gob);

     if (mouseX < 0 || mouseX + gob->box.w > Camera::tela.x || mouseY < 0 || mouseY + gob->box.h > Camera::tela.y) {
        if (mouseX < 0) {
            mouseX = 0; 
        }
        if (mouseX + gob->box.w > Camera::tela.x) {
            mouseX = Camera::tela.x - gob->box.w;
        }
        if (mouseY < 0) {
            mouseY = 0;
        }
        if (mouseY + gob->box.h > Camera::tela.y) {
            mouseY = Camera::tela.y - gob->box.h;
        }
        // cout << "Saiu fora" << " objPos.x: " << mouseX << " objPos.y: " << mouseY << endl << endl;
    }

    gob->box.x = mouseX;
    gob->box.y = mouseY;
    gob->AddComponent(penguin);
    gob->AddComponent(boom);
    // gob->AddComponent(logik);
    gob->AddComponent(notCam);

    shared_ptr<GameObject> gobShared(gob);

    objectArray.push_back(gobShared);

    if (started) {
        gobShared->Start();
        weak_ptr<GameObject> gobWeak(gobShared);
        return gobWeak;
    }

    weak_ptr<GameObject> gobWeak;
    return gobWeak;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
    for(int i=0; i<objectArray.size(); i++) {
        if (objectArray[i].get() == go) {
            weak_ptr<GameObject> weakPtrReturn(objectArray[i]);
            return weakPtrReturn;
        }
    }
    weak_ptr<GameObject> weakPtrReturn;
    return weakPtrReturn;
}
