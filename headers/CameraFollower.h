#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class CameraFollower : public Component {

    public:
        CameraFollower(GameObject& associated, Vec2 offset = {0, 0});

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;

        void Start() override;

    private:
        Vec2 offset;
};


#endif