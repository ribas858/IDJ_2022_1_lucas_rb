#ifndef MUSIC_H
#define MUSIC_H

#include "../headers/GameObject.h"

class Music : public Component {

    public:
        Music(GameObject& associated);
        Music(GameObject& associated, string file);
        ~Music();

        void Play(int times = -1);
        void Stop(int msToStop = 1500);
        void Open(string file);
        bool IsOpen();

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;


    private:
        Mix_Music* music;
};

#endif