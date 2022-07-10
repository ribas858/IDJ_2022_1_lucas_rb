#ifndef FACE_H
#define FACE_H

#include "../headers/GameObject.h"

class Face : public Component {
    public:
        Face(GameObject& associated);
        void Damage (int damage);

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;

    private:
        int hitpoints;
};

#endif