#ifndef SOUND_H
#define SOUND_H

#include "../headers/GameObject.h"

class Sound : public Component {
    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated, string file);
        ~Sound();

        void Play( int times = 1);
        void Stop();
        void Open(string file);
        bool IsOpen();

        void Update(float dt) override;
        void Render() override;
        bool Is(string type) override;
        void Start() override;

    private:
        Mix_Chunk* chunk;
        int channel;
};

#endif