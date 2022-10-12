#include "../headers/State.h"


State::State() {
    popRequested = false;
    quitRequested = false;
    started = false;
}

State::~State() {
    objectArray.clear();
}

void State::LoadAssets() {

}

void State::Update(float dt) {

}

void State::Render() {

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

bool State::PopRequested() {
    return popRequested;
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::StartArray() {
    for (int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Start();
    }
}

void State::UpdateArray(float dt) {
    for(int i=0; i<objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }
}

void State::RenderArray() {
    for (vector<shared_ptr<GameObject>>::iterator ob = objectArray.begin(); ob != objectArray.end(); ob++) {
        (*ob)->Render();
    }
}

void State::ClearObject() {
    for(int i=0; i<objectArray.size(); i++) {
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            // cout << "limpa no objectArray" << endl << endl;
        }
    }
}

Text* State::GetText(int id) {
    for(int i=0; i<objectArray.size(); i++) {
       Component* cp = objectArray[i]->GetComponent(to_string(id));
        if (cp) {
            Text* tx = (Text*)cp;
            return tx;
        }
    }
    return nullptr;
}