#ifndef RESOURCES_H
#define RESOURCES_H

#include "../headers/base_includes.h"

class Resources {
    public:
        SDL_Texture* GetImage(string file);
        void ClearImages();
        Mix_Music* GetMusic(string file);
        void ClearMusics();
        Mix_Chunk* GetSound(string file);
        void ClearSounds();

    private:
        unordered_map<string, SDL_Texture*> imageTable;
        unordered_map<string, Mix_Music*> musicTable;
        unordered_map<string, Mix_Chunk*> soundTable;
};

#endif