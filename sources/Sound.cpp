#include "../headers/Sound.h"
#include "../headers/Resources.h"

void Sound::Start() {
    // cout << "start sound" << endl;
}

Sound::Sound(GameObject& associated) : Component(associated) {
    chunk = nullptr;
}

Sound::Sound(GameObject& associated, string file) : Sound(associated) {
    Open(file);
}

Sound::~Sound() {
    
}

void Sound::Play( int times) {
    channel = Mix_PlayChannel(-1, chunk, times-1);
}

void Sound::Stop() {
    if (chunk != nullptr) {
        Mix_HaltChannel(channel);
    }
}
 
void Sound::Open(string file) {
    if(!Resources::FindSound(file)) {
        chunk = Mix_LoadWAV(file.c_str());
        if (!chunk) {
            SDL_Log("Erro ao carregar Som: %s", Mix_GetError());
        } else {
            //cout << "Som Carregado!!" << endl << endl;
            Resources::InsertSound(file, chunk);
        }
    } else {
        //cout << "Som ja está aberto" << endl;
        //cout << "Buscando Som na tabela..." << endl << endl;
        chunk = Resources::GetSound(file);
    }
}

bool Sound::IsOpen() {
    if (chunk) {
        return true;
    } else {
        return false;
    }
}

void Sound::Update(float dt) {

}

void Sound::Render() {
}

bool Sound::Is(string type) {
    string sound = "Sound";
    if (type == sound){
        return true;
    } else {
        return false;
    }
}