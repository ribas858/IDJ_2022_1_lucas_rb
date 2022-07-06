#ifndef STATE_H
#define STATE_H

#include "../headers/GameObject.h"

#include "../headers/Sprite.h"
#include "../headers/Music.h"

class State {
    public:
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();

        void Input();
        void AddObject(int mouseX, int mouseY);
    
    private:
        Sprite* bg;
        Music* music;
        bool quitRequested;
        vector<unique_ptr<GameObject>> objectArray;
};

#endif