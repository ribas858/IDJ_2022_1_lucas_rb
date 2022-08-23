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

        bool FindKey(int key);

        const int& GetUpdateCounter() const {
            return updateCounter;
        }

        int& SetUpdateCounter() {
            return updateCounter;
        }

        const string& GetLastAdressFace() const {
            return lastAdressFace;
        }

        string& SetLastAdressFace() {
            return lastAdressFace;
        }

        const int& GetLastFrame() const {
            return lastFrame;
        }

        int& SetLastFrame() {
            return lastFrame;
        }


    private:
        InputManager() = default;
        ~InputManager() = default;
        InputManager(const InputManager&)= delete;
        InputManager& operator=(const InputManager&)= delete;

        bool mouseState[6] = { false };
        int mouseUpdate[6] = { 0 };
        
        unordered_map<int, bool> keyState;
        unordered_map<int, int> keyUpdate;

        bool quitRequested = false;
        int updateCounter = 0;
        int mouseX = 0;
        int mouseY = 0;

        string lastAdressFace = "";
        int lastFrame = 0;
        
};

#endif