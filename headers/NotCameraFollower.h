#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "../headers/GameObject.h"

class NotCameraFollower : public Component {

    public:
        NotCameraFollower(GameObject& go);

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;

    private:
};


#endif