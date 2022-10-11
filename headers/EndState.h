#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "../headers/State.h"

class EndState : public State {
    public:
        EndState();
        ~EndState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    
    private:
};

#endif