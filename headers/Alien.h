#ifndef ALIEN_H
#define ALIEN_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class Alien : public Component, public Being {
    
    public:
        Alien(GameObject & associated, int nMinions);
        ~Alien();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(string type);

        Vec2 GetSpeed();
        Vec2 GetDesloc();

        void NotifyCollision(GameObject& other) override;
        
        void NewShoot(Vec2 destination);
        int id;
        static void CleanGlobals();

    private:
        // class Action {
        //     public:
        //         enum class ActionType { MOVE, SHOOT };
                
        //         Action(ActionType type, float x, float y) : type(type), pos(x,y) { }

        //         ActionType type;
        //         Vec2 pos;
        // };
        // queue<Action> taskQueue;

        Vec2 speed;
        int hp;
        int nMinions;

        vector <weak_ptr<GameObject>> minionArray;
        static Vec2 desloc;
        static Vec2 fimDesloc;
        static int flag;
        static Vec2 inicialPos;

        /////////////////////////////////
        
        enum class AlienState { MOVING, RESTING };
        AlienState state;
        Timer restTimer;
        Vec2 destination;

        int counTiros = 0;
        Timer tiros;



};

#endif