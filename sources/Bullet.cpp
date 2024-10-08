#include "../headers/Bullet.h"
#include "../headers/Sprite.h"

Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component(associated), distanceLeft(maxDistance), damage(damage) {
    Sprite* bulletSprite = new Sprite(associated, sprite);
    associated.AddComponent(bulletSprite);
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