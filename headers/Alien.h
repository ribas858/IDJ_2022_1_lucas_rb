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

        queue<Action> taskQueue;
        vector <unique_ptr<Component>> minionArray;

        static Vec2 posD;
        static Vec2 flagDs;
        static int flagSpeed;


};

#endif