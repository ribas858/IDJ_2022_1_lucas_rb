#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class PenguinBody : public Component, public Being {
    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);

        static PenguinBody* player;
        void NotifyCollision(GameObject& other) override;
        Rect GetBoxPenguin();
        int GetHp();

    private:
        weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;

        bool desacelerarFrente = false;
        bool desacelerarBack = false;
        float aceleracao;
        float speedAcc;

        bool limiteMapa = false;
        Vec2 posAux;

};





#endif