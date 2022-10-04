#include "../headers/Bullet.h"
#include "../headers/Sprite.h"
#include "../headers/Collider.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, bool target, int frameCount, string sprite) : Component(associated),
        distanceLeft(maxDistance), damage(damage), targetsPlayer(target) {
    
    Sprite* bulletSprite = new Sprite(associated, sprite, frameCount, 0.07);
    associated.AddComponent(bulletSprite);
    Collider* cold = new Collider(associated);
    associated.AddComponent(cold);
    Bullet::speed.x = cos(angle) * speed;
    Bullet::speed.y = sin(angle) * speed;
}

void Bullet::Update(float dt) {
    Vec2 ds;
    ds.x = speed.x * dt;
    ds.y = speed.y * dt;

    associated.box.x += ds.x;
    associated.box.y += ds.y;

    float DS = sqrt(pow(ds.x, 2) + pow(ds.y, 2));

    distanceLeft -= DS;

    // cout << "distance left: " << distanceLeft << endl;

    if (distanceLeft <= 0) {
        associated.RequestDelete();
    }

}

void Bullet::Render() {

}

bool Bullet::Is(string type) {
    string bullet = "Bullet";
    if (type == bullet){
        return true;
    } else {
        return false;
    }
}

int Bullet::GetDamage() {
    return damage;
}

void Bullet::NotifyCollision(GameObject& other) {
    // if (other.GetComponent("Being")) {
    //     associated.RequestDelete();
    // }
}