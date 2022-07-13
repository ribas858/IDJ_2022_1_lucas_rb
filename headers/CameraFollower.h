#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "../headers/GameObject.h"

class CameraFollower : public Component {

    public:
        CameraFollower(GameObject& go);

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;

    private:
};


#endif