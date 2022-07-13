#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "../headers/base_includes.h"

class InputManager {
    public:
        void Update();

        bool KeyPress(int key);
        bool KeyRelease(int key);
        bool IsKeyDown(int key);

        bool MousePress(int button);
        bool MouseRelease(int button);
        bool IsMouseDown(int button);

        int GetMouseX();
        int GetMouseY();

        bool QuitRequested();

        InputManager& GetInstance();

    private:
        ~InputManager();

        bool mouseState[6];
        int mouseUpdate[6];

        // keyState;
        // keyUpdate;

        bool quitRequested;
        int updateCounter;
        int mouseX;
        int mouseY;

        InputManager();
        
};

#endif