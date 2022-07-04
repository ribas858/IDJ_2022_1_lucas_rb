#pragma once
#include "base_includes.h"

#include "State.h"



class Game {

    public:

        ~Game ();
        void Run(string title, int width, int height);

        static Game& GetInstance();
        State& GetState();
        SDL_Renderer* GetRenderer();
    
    private:
        void Init_Sdl();
        void Init_Sdl_Image();
        void Init_Sdl_Audio();
        void Cria_Window(const char* title, int x, int y, int w, int h, Uint32 flags);
        void Destroy_Window();
        void Close_Sdl_Audio();

        static Game * instance;
        SDL_Window* window;
        SDL_Renderer* renderer;
        State* state;

        Game (string title, int width, int height) {
            if (instance) {
                cout << "|===-> Erro no Padrão Singleton :: " << endl;
                exit(EXIT_SUCCESS);
            } else {
                // cout << "instance == null" << endl;
                instance = this;
            }
            window = nullptr;
            renderer = nullptr;
            state = nullptr;
            Run(title, width, height);
        }
};