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

        static InputManager& GetInstance();

    private:
        InputManager() {
            cout << "kk eae man" << endl;
            mouseState[6] = {};
            mouseUpdate[6] = {};
            quitRequested = false;
            updateCounter = 0;
            mouseX = 0;
            mouseY = 0;
        }
        
        ~InputManager() {
            cout << "kk destroy" << endl;
        }

        bool mouseState[6];
        int mouseUpdate[6];

        unordered_map<int, bool> keyState;
        unordered_map<int, int> keyUpdate;

        bool quitRequested;
        int updateCounter;
        int mouseX;
        int mouseY;

        
};

#endif