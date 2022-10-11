#ifndef MINION_H
#define MINION_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"


class Minion : public Component, public Being {
    
    public:
        Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg, bool lib, int id, int nMini, Vec2 scale);
        
        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vec2 target);

        void NotifyCollision(GameObject& other) override;
        static void CleanGlobals();

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

        static vector<int> lastMiniLiberado;
        static vector<int> nextMiniLiberado;
        static vector<int> resetPos;
        static vector<int> allFree;

        double ang;
        Vec2 originalScale;
        static vector<float> limitePisca;
        static vector<float> somaScale;

        Timer lib;
        int idAlien = 0;
};


#endif