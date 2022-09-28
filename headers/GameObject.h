#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../headers/Rect.h"
#include "../headers/Component.h"

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

        void Start();

        bool started;
        double angleDeg;
        bool cam;

    private:
        vector <unique_ptr<Component>> components;
        bool isDead;

};

#endif