#ifndef ALIEN_H
#define ALIEN_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class Alien : public Component {
    
    public:
        Alien(GameObject & associated, int nMinions);
        ~Alien();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);

        Vec2 GetSpeed();
        Vec2 GetDesloc();

    private:
        class Action {
            public:
                enum class ActionType { MOVE, SHOOT };
                
                Action(ActionType type, float x, float y) : type(type), pos(x,y) { }

                ActionType type;
                Vec2 pos;
        };

        Vec2 speed;
        int hp;
        int nMinions;
        Vec2 camPos;

        queue<Action> taskQueue;
        vector <weak_ptr<GameObject>> minionArray;

        static Vec2 desloc;
        static Vec2 fimDesloc;
        static int flag;
        static Vec2 inicialPos;



};

#endif