#ifndef SPRITE_H
#define SPRITE_H

#include "../headers/Component.h"


class Sprite : public Component {
    public:
        Sprite() : Component(associated), texture(nullptr) { }
        
        Sprite(string file) : Component(associated), texture(nullptr) { Open(file); }
        
        ~Sprite() override {
            SDL_DestroyTexture(texture);
        }
        
        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void Render() override;
        void Update(float dt) override;
        bool Is(string type) override;

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;  
};

#endif