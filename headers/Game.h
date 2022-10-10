#ifndef GAME_H
#define GAME_H

#include "../headers/GameObject.h"
#include "../headers/State.h"

class Game {

    public:
        Game (string title, int width, int height);
        ~Game ();

        static Game& GetInstance();
        SDL_Renderer* GetRenderer();
        State& GetCurrentState();

        void Push(State* state);
        void Run();
        float GetDeltaTime();
        ////////////////////////////

    private:
        void CalculateDeltaTime();

        float frameStart;
        float dt;

        static Game * instance;

        State* storedState;
        SDL_Window* window;
        SDL_Renderer* renderer;
        stack<unique_ptr<State>> stateStack;

        /////////////////////////////
        void Init_Sdl();
        void Init_Sdl_Image();
        void Init_Sdl_Audio();
        void Cria_Window(const char* title, int x, int y, int w, int h, Uint32 flags);
        void Destroy_Window();
        void Close_Sdl_Audio();
        string title;
        int width;
        int height;

        
};

#endif