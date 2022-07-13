#ifndef CAMERA_H
#define CAMERA_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class Camera {

    public:
        void Follow(GameObject* newFocus);
        void Unfollow();
        void Update(float dt);

        Vec2 pos;
        Vec2 speed;

    private:
        GameObject* focus;

};

#endif