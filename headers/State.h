#ifndef STATE_H
#define STATE_H

#include "../headers/GameObject.h"
#include "../headers/Music.h"

class State {
    public:
        State();
        ~State();

        bool QuitRequested();
        void LoadAssets();
        void Update(float dt);
        void Render();
        // void AddObject(int mouseX, int mouseY);

        void Start();
        weak_ptr<GameObject> AddObject(GameObject* go);
        weak_ptr<GameObject> GetObjectPtr(GameObject* go);


    
    private:
        class Sprite* bg;
        Music music;
        bool quitRequested;
        
        bool started;
        vector<shared_ptr<GameObject>> objectArray;
};

#endif