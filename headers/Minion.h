#ifndef MINION_H
#define MINION_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"


class Minion : public Component {
    
    public:
        Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg, bool lib, int id, int nMini, Vec2 scale);
        
        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vec2 target);

    private:
        weak_ptr<GameObject> alienCenter;
        Vec2 origin;
        Vec2 xyLinha;
        Vec2 xy;

        Vec2 sourceShoot;

        float arc;
        float diametro;
        float releaseLimit;

        int numMinions;
        bool liberado;
        int id;

        static int lastMiniLiberado;
        static int nextMiniLiberado;
        static int resetPos;
        static int allFree;

        double ang;
};


#endif