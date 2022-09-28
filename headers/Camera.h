#ifndef CAMERA_H
#define CAMERA_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class Camera {

    public:
        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);

        static Vec2 pos;
        static Vec2 speed;

        static Vec2 tileSetTam;

        // static Vec2 flag;
        static Vec2 mouseAcc;
        static Vec2 tela;
        static Vec2 lastPos;
        static float accSpeed;

        static Vec2 focusAux;

    private:
        static GameObject* focus;

};

#endif