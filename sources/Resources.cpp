#include "../headers/Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;


SDL_Texture* Resources::GetImage(string file) {
    if (FindImage(file)) {
        return imageTable.find(file)->second;
    }
    return nullptr;
}

void Resources::ClearImages() {
    for (auto img = imageTable.begin(); img != imageTable.end(); ++img) {
        SDL_DestroyTexture(img->second);
    }
    imageTable.clear();
}

Mix_Music* Resources::GetMusic(string file) {
    Mix_Music* compile_test;
    return compile_test;
}

void Resources::ClearMusics() {
    for (auto ms = musicTable.begin(); ms != musicTable.end(); ++ms) {
        Mix_FreeMusic(ms->second);
    }
    musicTable.clear();
}

Mix_Chunk* Resources::GetSound(string file) {
    if (FindSound(file)) {
        return soundTable.find(file)->second;
    }
    return nullptr;
}

void Resources::ClearSounds() {
    for (auto sd = soundTable.begin(); sd != soundTable.end(); ++sd) {
        Mix_FreeChunk(sd->second);
    }
    soundTable.clear();
}

bool Resources::FindImage(string file) {
    if (imageTable.find(file) == imageTable.end()) {
        return false;
    } else {
        return true;
    }
}

void Resources::InsertImage(string file, SDL_Texture* texture) {
    imageTable.insert({file, texture});
}

bool Resources::FindSound(string file) {
    if (soundTable.find(file) == soundTable.end()) {
        return false;
    } else {
        return true;
    }
}

void Resources::InsertSound(string file, Mix_Chunk* chunk) {
    soundTable.insert({file, chunk});
}

bool Resources::FindMusic(string file) {
    if (musicTable.find(file) == musicTable.end()) {
        return false;
    } else {
        return true;
    }
}

void Resources::InsertMusic(string file, Mix_Music* music) {
    musicTable.insert({file, music});
}