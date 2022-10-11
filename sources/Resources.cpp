#include "../headers/Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;
unordered_map<string, TTF_Font*> Resources::fontTable;


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
    if (FindMusic(file)) {
        return musicTable.find(file)->second;
    }
    return nullptr;
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

TTF_Font* Resources::GetFont(string file_size) {
    if (FindFont(file_size)) {
        return fontTable.find(file_size)->second;
    }
    return nullptr;
}

void Resources::ClearFonts() {
    for (auto ft = fontTable.begin(); ft != fontTable.end(); ++ft) {
        TTF_CloseFont(ft->second);
    }
    fontTable.clear();
}

bool Resources::FindFont(string file_size) {
    if (fontTable.find(file_size) == fontTable.end()) {
        return false;
    }
    return true;
}

void Resources::InsertFont(string file, TTF_Font* font, int ptsize) {
    fontTable.insert({file+to_string(ptsize), font});
}