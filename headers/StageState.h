#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "../headers/GameObject.h"
#include "../headers/TileSet.h"
#include "../headers/Music.h"
#include "../headers/State.h"

class StageState : public State {
    public:
        StageState();
        ~StageState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    
    private:
        TileSet* tileSet;
        Music backgroundMusic;
};

#endif