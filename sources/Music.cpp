#include "../headers/Music.h"
#include "../headers/Game.h"

#include "../headers/Resources.h"

Music::Music() {
    cout << "\nEntrou em MUSIC" << endl;
    music = nullptr;
}

Music::Music(std::string file) : Music() {
    Open(file);
}

Music::~Music() {
    Stop();
}

void Music::Play(int times) {
    Mix_PlayMusic(music, -1);
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    
    if(!Resources::FindMusic(file)) {
        music = Mix_LoadMUS(file.c_str());
        if (!music) {
            SDL_Log("Erro ao carregar Musica: %s", Mix_GetError());
        } else {
            cout << "Musica Carregada!!" << endl;
            Resources::InsertMusic(file, music);
        }
    } else {
        cout << "Musica ja está aberta" << endl;
        cout << "Buscando Musica na tabela..." << endl << endl;
        music = Resources::GetMusic(file);
    }
    
}

bool Music::IsOpen() {
    if (music) {
        return true;
    } else {
        return false;
    }
}