#include "../headers/GameObject.h"


GameObject::GameObject() {
    isDead = false;
}

GameObject::~GameObject() {
    for (vector<Component*>::reverse_iterator cp = components.rbegin(); cp != components.rend(); cp++) {
        delete (*cp);
    }
    components.clear();
}

void GameObject::Update(float dt) {
    for (vector<Component*>::iterator cp = components.begin(); cp != components.end(); cp++) {
        (*cp)->Update(dt);
    }
}

void GameObject::Render() {
    for (vector<Component*>::iterator cp = components.begin(); cp != components.end(); cp++) {
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
    components.push_back(cpt);
}

void GameObject::RemoveComponent(Component* cpt) {
    if(!components.empty()) {
        components.pop_back();
    }
}

Component* GetComponent(string type) {
    Component* a;
    return a;
}