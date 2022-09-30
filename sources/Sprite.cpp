#include "../headers/Sprite.h"

#include "../headers/Game.h"

#include "../headers/Resources.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"
//Resources* recurso = new Resources();

void Sprite::Start() {
    // cout << "start sprite" << endl;
}

Sprite::Sprite(GameObject& associated) : Component(associated) {
    scale.x = 1;
    scale.y = 1;
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file) : Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() {

}


void Sprite::Open(string file) {
    if(!Resources::FindImage(file)){
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
        
        if (!texture) {
            SDL_Log("Impossível carregar imagem: %s", SDL_GetError());
        } else {
            cout << "Sprite carregado com sucesso!!" << endl;
            Resources::InsertImage(file, texture);
        }
    } else {
        cout << "Sprite já foi carregado..." << endl;
        cout << "Buscando na tabela..." << endl;
        texture = Resources::GetImage(file);
        //Open(file);
    }

    if(texture) {
        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        SetClip(0, 0, width, height);
    }
}


void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.w = w;
    clipRect.h = h;
    clipRect.x = x;
    clipRect.y = y;
    // associated.box.x = x;
    // associated.box.y = y;
    associated.box.w = w;
    associated.box.h = h;
}

void Sprite::Render() {
    Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y, associated.angleDeg);  
}

void Sprite::Render(float x, float y, float angle) {
    SDL_Rect dstrect;
    dstrect.w = clipRect.w * scale.x;
    dstrect.h = clipRect.h * scale.y;
    dstrect.x = x;
    dstrect.y = y;
    
    SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
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


void Sprite::SetScale(float scaleX, float scaleY) {
    if (scaleX != 0) {
        scale.x = scaleX;
    }
    if (scaleY != 0) {
        scale.y = scaleY;
    }
    associated.box.w *= scale.x;
    associated.box.h *= scale.y;
    width = associated.box.w;
    height = associated.box.h;
}

void Sprite::SetScaleRender(float scaleX, float scaleY) {
    if (scaleX != 0) {
        scale.x = scaleX;
    }
    if (scaleY != 0) {
        scale.y = scaleY;
    }
}

Vec2 Sprite::GetScale() {
    return scale;
}