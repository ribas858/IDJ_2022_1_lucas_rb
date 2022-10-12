#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"
#include "../headers/Sprite.h"

class PenguinCannon : public Component, public Being {
    public:
        PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);

        void Update(float dt);
        void Render();
        bool Is(string type);

        void Shoot();
        void NotifyCollision(GameObject& other) override;

    private:
        weak_ptr<GameObject> pbody;
        float angle;

        float maxDistance;
        int damage;

        Vec2 origin;
        Vec2 xylinha;
        Timer time;

        int municao = 10;
        bool recarrega = false;
        bool cooldown = false;
        class Sound* recarga;

        Timer arranque;
        Sprite* sp = nullptr;

};

#endif