#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../headers/Component.h"
#include "../headers/Rect.h"

class GameObject {
    public:
        GameObject();
        ~GameObject();
        
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        
        Component* GetComponent(string type);

        Rect box;

    private:
        vector <Component*> components;
        bool isDead;

};

#endif