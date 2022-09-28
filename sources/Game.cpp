#include "../headers/Game.h"

#include "../headers/TileSet.h"
#include "../headers/Resources.h"

#include "../headers/InputManager.h"
#include "../headers/Camera.h"

void Game::Init_Sdl() {
    if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO || SDL_INIT_TIMER) != 0) {
        SDL_Log("Impossível inicializar a SDL: %s", SDL_GetError());
    } else {
        cout << "SUCESSO!! SDL" << endl;
    }
}

void Game::Init_Sdl_Image() {
    if (IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG || IMG_INIT_TIF) == 0) {
        SDL_Log("Impossível inicializar a biblioteca de IMAGENS: %s", IMG_GetError());
    } else {
        cout << "SUCESSO!! IMG SDL" << endl;
    }
}

void Game::Init_Sdl_Audio() {
    if (Mix_Init(MIX_INIT_FLAC || MIX_INIT_OGG || MIX_INIT_MP3 || MIX_INIT_MOD) == 0) {
        SDL_Log("Impossível inicializar a biblioteca de SONS: %s", Mix_GetError());
    } else {
        cout << "SUCESSO!! SONS SDL" << endl;
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
        SDL_Log("Erro Open Audio: %s", Mix_GetError());
    } else {
        cout << "SUCESSO!! Open Audio" << endl;
    }
}

//
void Game::Cria_Window(const char* title, int x, int y, int w, int h, Uint32 flags) {
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    if (window != nullptr){
        cout << "SUCESSO!! Window" << endl;
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer != nullptr){
            cout << "SUCESSO!! Render" << endl;
        } else {
            SDL_Log("Impossível Renderizar: %s", SDL_GetError());
        }
    } else {
        SDL_Log("Impossível criar Janela: %s", SDL_GetError());
    }
}

void Game::Destroy_Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::Close_Sdl_Audio() {
    Mix_CloseAudio();
    Mix_Quit();
}

Game::~Game() {
    // State
    Destroy_Window();
    Close_Sdl_Audio();
    IMG_Quit();
    SDL_Quit();
}

Game * Game::instance = nullptr;

Game & Game::GetInstance() {
  if (!instance) {
        cout << "CRIANDO NOVA INSTANCIA DA CLASSE GAME" << endl;
        instance = new Game("Lucas Junior Ribas - 160052289", 1024, 600);
    } else {
        //cout << "Já existe uma instancia da classe game!!" << endl;
    }
    return *instance;
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}

float Game::GetDeltaTime() {
    return dt / 1000;
}

void Game::Run(string title, int width, int height) {
    Init_Sdl();
    Init_Sdl_Image();
    Init_Sdl_Audio();
    Cria_Window(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    state = new State();
    Camera::tela.x = width;
    Camera::tela.y = height;

    // TileSet* t = new TileSet(40, 40, "images/tileset.png");
    // t->RenderTile(20, 800, 430);


    state->Start();

    while (!state->QuitRequested()) {
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        state->Update(GetDeltaTime());
        SDL_RenderClear(renderer);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);

        InputManager::GetInstance().SetUpdateCounter()++;

        if (InputManager::GetInstance().IsKeyDown(SDLK_d)) {
            cout << "dt: " << GetDeltaTime() << " segs" << endl;
        }      
    }

    Resources::ClearImages();
    Resources::ClearSounds();
    Resources::ClearMusics();
}