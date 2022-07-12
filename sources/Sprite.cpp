#include "../headers/Sprite.h"

#include "../headers/Game.h"

Sprite::Sprite(GameObject& associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(string file, GameObject& associated) : Component(associated) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    SDL_DestroyTexture(texture);
}


void Sprite::Open(string file) {
    if(!IsOpen()){
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        if (!texture) {
            SDL_Log("Impossível carregar imagem: %s", SDL_GetError());
        } else {
            cout << "Sprite carregado com sucesso!!" << endl;
            SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
            SetClip(0, 0, width, height);
        }
    } else {
        cout << "Sprite já foi carregado..." << endl;
        SDL_DestroyTexture(texture);
        Open(file);
    }
    
}


void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.w = w;
    clipRect.h = h;
    clipRect.x = x;
    clipRect.y = y;
    associated.box.x = x;
    associated.box.y = y;
    associated.box.w = w;
    associated.box.h = h;
}

void Sprite::Render() {
    SDL_Rect dstrect;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;
    dstrect.x = associated.box.x;
    dstrect.y = associated.box.y;
    //cout << "Render Sprite..." << endl;
    
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}

int Sprite::GetWidth() {
    return width;
}
int Sprite::GetHeight() {
    return height;
}

bool Sprite::IsOpen() {
    if (texture) {
        return true;
    } else {
        return false;
    }
}

void Sprite::Update(float dt) {
    
}

bool Sprite::Is(string type) {
    string sprite = "Sprite";
    if (type == sprite){
        return true;
    } else {
        return false;
    }
}

SDL_Rect Sprite::return_clipRect() {
    return clipRect;
}

SDL_Texture* Sprite::return_texture() {
    return texture;
}

void Sprite::Render(float x, float y) {
    SDL_Rect dstrect;
    dstrect.w = clipRect.w;
    dstrect.h = clipRect.h;
    dstrect.x = x;
    dstrect.y = y;
    
    SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
}