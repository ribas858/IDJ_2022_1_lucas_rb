#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class PenguinCannon : public Component {
    public:
        PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);

        void Update(float dt);
        void Render();
        bool Is(string type);

        void Shoot();

    private:
        weak_ptr<GameObject> pbody;
        float angle;

};





#endif