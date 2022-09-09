#ifndef GAME_H
#define GAME_H

#include "../headers/GameObject.h"
#include "../headers/State.h"

class Game {

    public:

        ~Game ();
        void Run(string title, int width, int height);

        static Game& GetInstance();
        class State& GetState();
        SDL_Renderer* GetRenderer();

        ////////////////////////////
        float GetDeltaTime();
    
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

        /////////////////////////////
        void CalculateDeltaTime() {
            temp_atual = SDL_GetTicks();
            dt = temp_atual - frameStart;
            frameStart = temp_atual;
        }


        float frameStart;
        float temp_atual;
        float dt;

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
            frameStart = 0;
            temp_atual = 0;
            dt = 0;
            Run(title, width, height);
        }
};

#endif