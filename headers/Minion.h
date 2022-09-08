#ifndef MINION_H
#define MINION_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class Minion : public Component {
    
    public:
        Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        
        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vec2 target);

    private:
        GameObject& alienCenter;
        float arc;
        Vec2 origin;

        static int flag;

};


#endif