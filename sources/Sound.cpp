#include "../headers/Sound.h"

Sound::Sound(GameObject& associated) : Component(associated) {
    chunk = nullptr;
}

Sound::Sound(GameObject& associated, string file) : Component(associated) {
    Open(file);
}

Sound::~Sound() {
    if(!chunk) {
        Stop();
        Mix_FreeChunk(chunk);
    }
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
    if(!IsOpen()) {
        chunk = Mix_LoadWAV(file.c_str());
        if (!chunk) {
            SDL_Log("Erro ao carregar Som: %s", Mix_GetError());
        } else {
            cout << "Som Carregado!!" << endl;
        }
    } else {
        cout << "Som ja está aberto" << endl;
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