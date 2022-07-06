#ifndef MUSIC_H
#define MUSIC_H

#include "../headers/Component.h"

class Music {

    public:
        Music();
        Music(string file);
        ~Music();

        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(string file);
        bool IsOpen();


    private:
        Mix_Music* music;
};

#endif