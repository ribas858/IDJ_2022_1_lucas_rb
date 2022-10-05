#ifndef SPRITE_H
#define SPRITE_H

#include "../headers/Component.h"
#include "../headers/Vec2.h"


class Sprite : public Component {
    public:
        Sprite(class GameObject& associated);
        
        Sprite(class GameObject& associated, string file, int frameCount = 1,
            float frameTime = 1, float secondsToSelfDestruct = 0);
        
        ~Sprite() override;
        
        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        int GetWidth();
        int GetHeight();
        bool IsOpen();

        void Render() override;
        void Update(float dt) override;
        bool Is(string type) override;

        void Render(float x, float y, float angle=0);

        void Start() override;

        SDL_Rect return_clipRect();
        SDL_Texture* return_texture();

        void SetScale(float scaleX, float scaleY);
        Vec2 GetScale();
        void SetScaleRender(float scaleX, float scaleY);

        ///////////////////////////////////////////////
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);

    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;  
        Vec2 scale;

        /////////////////////
        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;

        /////////////////////
        Timer selfDestructCount;
        float secondsToSelfDestruct;

};

#endif