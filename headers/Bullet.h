#ifndef BULLET_H
#define BULLET_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class Bullet : public Component {

    public:
        Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool target, int frameCount, string sprite);

        void Update(float dt);
        void Render();
        bool Is(string type);

        int GetDamage();
        void NotifyCollision(GameObject& other) override;
        bool targetsPlayer;

    private:
        Vec2 speed;
        float distanceLeft;
        int damage;
};



#endif