#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "../headers/base_includes.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

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
        const int& GetUpdateCounter() const;
        int& SetUpdateCounter();
        
        const int& GetLastFrame() const;
        int& SetLastFrame();

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
        int lastFrame = 0;
        
};

#endif