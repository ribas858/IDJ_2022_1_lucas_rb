#ifndef COMPONENT_H
#define COMPONENT_H

#include "../headers/base_includes.h"


class Component {

    public:
        Component(class GameObject& receive_associated) : associated(receive_associated) {}
        virtual ~Component();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(string type) = 0;
        
    protected:
        class GameObject& associated;
};

#endif