#ifndef STATE_H
#define STATE_H

#include "../headers/GameObject.h"
#include "../headers/Music.h"

class State {
    public:
        State();
        ~State();

        virtual void LoadAssets() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;

        virtual void Start() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;

        virtual weak_ptr<GameObject> AddObject(GameObject* object);
        virtual weak_ptr<GameObject> GetObjectPtr(GameObject* object);

        bool PopRequested();
        bool QuitRequested();

    protected:
        virtual void StartArray();
        virtual void UpdateArray(float dt);
        virtual void RenderArray();
        void ClearObject();

        bool popRequested;
        bool quitRequested;
        bool started;

        vector<shared_ptr<GameObject>> objectArray;
};

#endif