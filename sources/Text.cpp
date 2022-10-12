#include "../headers/Text.h"
#include "../headers/Game.h"
#include "../headers/Camera.h"
#include "../headers/Resources.h"


Text::Text(GameObject& associated, string fontFile, int fontSize,
    TextStyle style, string text, SDL_Color color, int id, float time) : Component(associated), 
    fontFile(fontFile), fontSize(fontSize), style(style), text(text), color(color), id(id), time(time) {

    font = nullptr;
    texture = nullptr;
    RemakeTexture();
}

Text::~Text() {
    if(texture){
        SDL_DestroyTexture(texture);
    }
}

void Text::RemakeTexture() {
    
    if(!texture){
        //cout << "RemakeTexture - Textura nova" << endl;
        if(!Resources::FindFont(fontFile + to_string(fontSize))) {
            TTF_Font* font = TTF_OpenFont (fontFile.c_str(), fontSize);
            if(font) {
                Resources::InsertFont(fontFile, font, fontSize);

                SDL_Surface* surface = nullptr;
                if(style == TextStyle::SOLID) {
                    surface = TTF_RenderText_Solid(font, text.c_str(), color);
                }
                else if(style == TextStyle::SHADED) {
                    surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0, 0});
                }
                else if(style == TextStyle::BLENDED) {
                    surface = TTF_RenderText_Blended(font, text.c_str(), color);
                }
                
                texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

                if(texture) {
                    int width = 0, height = 0;
                    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
                    associated.box.w = width;
                    associated.box.h = height;
                    associated.box.x = associated.box.PosCenter().x;
                    associated.box.y = associated.box.PosCenter().y; 
                }
                SDL_FreeSurface(surface);
                surface = nullptr;
            } else {
                cout << "Fonte invalida!!" << endl;
            }
        } else {
            // cout << "Fonte ja existe na tabela!!" << endl;

            font = Resources::GetFont(fontFile + to_string(fontSize));
            if(font) {
                Resources::InsertFont(fontFile, font, fontSize);

                SDL_Surface* surface = nullptr;
                if(style == TextStyle::SOLID) {
                    surface = TTF_RenderText_Solid(font, text.c_str(), color);
                }
                else if(style == TextStyle::SHADED) {
                    surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0, 0});
                }
                else if(style == TextStyle::BLENDED) {
                    surface = TTF_RenderText_Blended(font, text.c_str(), color);
                }
                
                texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

                if(texture) {

                    int width = 0, height = 0;
                    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
                    associated.box.x = associated.box.PosCenter().x;
                    associated.box.y = associated.box.PosCenter().y;
                    associated.box.w = width;
                    associated.box.h = height;
                }
                
                SDL_FreeSurface(surface);
                surface = nullptr;
            } else {
                cout << "Fonte invalida!!" << endl;
            }
        }

    } else {
        //cout << "RemakeTexture - Textura já existe" << endl;
        SDL_DestroyTexture(texture);
        texture = nullptr;

        if(!Resources::FindFont(fontFile + to_string(fontSize))) {
            TTF_Font* font = TTF_OpenFont (fontFile.c_str(), fontSize);
            if(font) {
                Resources::InsertFont(fontFile, font, fontSize);

                SDL_Surface* surface = nullptr;
                if(style == TextStyle::SOLID) {
                    surface = TTF_RenderText_Solid(font, text.c_str(), color);
                }
                else if(style == TextStyle::SHADED) {
                    surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0, 0});
                }
                else if(style == TextStyle::BLENDED) {
                    surface = TTF_RenderText_Blended(font, text.c_str(), color);
                }
                
                texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

                if(texture) {

                    int width = 0, height = 0;
                    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
                    //associated.box.x = associated.box.PosCenter().x;
                    //associated.box.y = associated.box.PosCenter().y;
                    associated.box.w = width;
                    associated.box.h = height;
                }
                
                SDL_FreeSurface(surface);
                surface = nullptr;
            } else {
                cout << "Fonte invalida!!" << endl;
            }
        } else {
            //cout << "Fonte ja existe na tabela!!" << endl;

            font = Resources::GetFont(fontFile + to_string(fontSize));
            if(font) {
                Resources::InsertFont(fontFile, font, fontSize);
                
                SDL_Surface* surface = nullptr;
                if(style == TextStyle::SOLID) {
                    surface = TTF_RenderText_Solid(font, text.c_str(), color);
                }
                else if(style == TextStyle::SHADED) {
                    surface = TTF_RenderText_Shaded(font, text.c_str(), color, {0, 0, 0, 0});
                }
                else if(style == TextStyle::BLENDED) {
                    surface = TTF_RenderText_Blended(font, text.c_str(), color);
                }
                
                texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);

                if(texture) {

                    int width = 0, height = 0;
                    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
                    //associated.box.x = associated.box.PosCenter().x;
                    //associated.box.y = associated.box.PosCenter().y;
                    associated.box.w = width;
                    associated.box.h = height;
                }
                
                SDL_FreeSurface(surface);
                surface = nullptr;
            } else {
                cout << "Fonte invalida!!" << endl;
            }
        }

    }
}

void Text::Update(float dt) {
    if (time > 0) {
        Pisca(dt);
    }
}

void Text::Render() {

    if (texture && ativar) {
        
        SDL_Rect clipRect;
        clipRect.x = 0;
        clipRect.y = 0;
        clipRect.w = associated.box.w;
        clipRect.h = associated.box.h;

        SDL_Rect dstrect;
        dstrect.x = associated.box.x - Camera::pos.x;
        dstrect.y = associated.box.y - Camera::pos.y;
        dstrect.w = associated.box.w;
        dstrect.h = associated.box.h;
        
        SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    }
    
}

bool Text::Is (string type) {
    string tx = "Text";
    int i = -1;
    if(isAllDigit(type)) {
        i = stoi(type);
    }
    if (i == -1) {
        if (type == tx) {
            return true;
        } else {
            return false;
        }
    } else {
        if (i == id) {
            return true;
        } else {
            return false;
        }
    }
}

void Text::SetText (string text) {
    Text::text = text;
    RemakeTexture();
}

void Text::SetColor (SDL_Color color) {
    Text::color = color;
    RemakeTexture();
}

void Text::SetStyle (TextStyle style) {
    Text::style = style;
    RemakeTexture();
}

void Text::SetFontFile (string fontFile) {
    Text::fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize (int fontSize) {
    Text::fontSize = fontSize;
    RemakeTexture();
}

void Text::SetAtivar(bool flag) {
    ativar = flag;
}

void Text::Pisca(float dt) {
    texto.Update(dt);

    if(texto.Get() > time) {
        SetAtivar(false);
    } else {
        SetAtivar(true);
    }
    if(texto.Get() > time*1.5) {
        texto.Restart();
    }
}

bool Text::isAllDigit(string dig) {
    int flag = 0;
    for (int i=0; i<dig.size(); i++) {
        if (!isdigit(dig[i])) {
            flag++;
        }
    }
    if (flag > 0) {
        return false;
    } else {
        return true;
    }
}

int Text::GetId() {
    return id;
}