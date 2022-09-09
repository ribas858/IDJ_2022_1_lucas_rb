#ifndef MINION_H
#define MINION_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"


class Minion : public Component {
    
    public:
        Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg, bool lib, int id, int nMini);
        
        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vec2 target);

    private:
        weak_ptr<GameObject> alienCenter;
        float arc;

        Vec2 origin;
        float diametro;
        float pixelsAjust;

        static int lastMiniLiberado;

        static int nextMiniLiberado;
        
        static int resetPos;

        static int flag;

        int id;

        bool liberado;

        int numMinions;

        Vec2 xyLinha;
        Vec2 xy;


};


#endif