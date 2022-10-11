#ifndef TEXT_H
#define TEXT_H

#include "../headers/GameObject.h"
#include "../headers/Vec2.h"

class Text : public Component {
    public:
        enum class TextStyle { SOLID, SHADED, BLENDED };

        Text(GameObject& associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color, float time = 0);
        ~Text();
        void Update(float dt);
        void Render() override;
        bool Is(string type);
        void SetText(string text);
        void SetColor(SDL_Color color);
        void SetStyle(TextStyle style);
        void SetFontFile(string fontFile);
        void SetFontSize(int fontSize);

        void SetAtivar(bool flag);
        void Pisca(float dt);

    private:
        void RemakeTexture();

        TTF_Font* font;
        SDL_Texture* texture;
        string text;
        TextStyle style;
        string fontFile;
        int fontSize;
        SDL_Color color;

        bool ativar = true;
        Timer texto;
        float time;

};


#endif