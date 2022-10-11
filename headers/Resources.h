#ifndef RESOURCES_H
#define RESOURCES_H

#include "../headers/base_includes.h"

class Resources {
    public:
        static SDL_Texture* GetImage(string file);
        static void ClearImages();

        static Mix_Music* GetMusic(string file);
        static void ClearMusics();

        static Mix_Chunk* GetSound(string file);
        static void ClearSounds();

        static TTF_Font* GetFont(string file_size);
        static void ClearFonts();

        static bool FindImage(string file);
        static void InsertImage(string file, SDL_Texture* texture);

        static bool FindSound(string file);
        static void InsertSound(string file, Mix_Chunk* chunk);

        static bool FindMusic(string file);
        static void InsertMusic(string file, Mix_Music* music);

        static bool FindFont(string file_size);
        static void InsertFont(string file, TTF_Font* font, int ptsize);

    private:
        static unordered_map<string, SDL_Texture*> imageTable;
        static unordered_map<string, Mix_Music*> musicTable;
        static unordered_map<string, Mix_Chunk*> soundTable;
        static unordered_map<string, TTF_Font*> fontTable;
};

#endif