#pragma once
#include "../headers/base_includes.h"

#include "Sprite.h"
#include "Music.h"

class State {
    public:
        State();
        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
    
    private:
        Sprite* bg;
        Music* music;
        bool quitRequested;
};