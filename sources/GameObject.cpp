#include "../headers/GameObject.h"

void GameObject::Start()  {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Start();
    }
    started = true;
}

GameObject::GameObject() : started(false), isDead(false), angleDeg(0) {
    box.w = 0;
    box.h = 0;
    box.x = 0;
    box.y = 0;
}

GameObject::~GameObject() {
    for (vector<unique_ptr<Component>>::reverse_iterator cp = components.rbegin(); cp != components.rend(); cp++) {
        (*cp).reset();
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for (vector<unique_ptr<Component>>::iterator cp = components.begin(); cp != components.end(); cp++) {
        (*cp)->Update(dt);
    }
}

void GameObject::Render() {
    for (vector<unique_ptr<Component>>::iterator cp = components.begin(); cp != components.end(); cp++) {
        (*cp)->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component* cpt) {
    if(started) {
        cpt->Start();
    }
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    if(!components.empty()) {
        components.pop_back();
    }
}

Component* GameObject::GetComponent(string type) {
    for (int i = 0; i < components.size(); i++) {
        if(components[i]->Is(type)) {
            return components[i].get();
        }
    }
    return nullptr;
}