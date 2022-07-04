#include "../headers/Music.h"
#include "../headers/Game.h"

Music::Music() {
    cout << "Entrou em MUSIC" << endl;
    music = nullptr;
}

Music::~Music() {
    Stop();
    Mix_FreeMusic(music);
}

Music::Music(string file) {
    music = nullptr;
    Open(file);
}

void Music::Play(int times) {
    Mix_PlayMusic(music, -1);
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    
    if(!IsOpen()) {
        music = Mix_LoadMUS("sounds/stageState.ogg");
        if (!music) {
            SDL_Log("Erro ao carregar Musica: %s", Mix_GetError());
        } else {
            cout << "Musica Carregada!!" << endl;
        }
    } else {
        cout << "Musica ja está aberta" << endl;
    }
    
}

bool Music::IsOpen() {
    if (music) {
        return true;
    } else {
        return false;
    }
}