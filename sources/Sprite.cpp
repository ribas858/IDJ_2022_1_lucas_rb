#include "../headers/Sprite.h"

#include "../headers/Game.h"

#include "../headers/Resources.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"

void Sprite::Start() {
    // cout << "start sprite" << endl;
}

Sprite::Sprite(GameObject& associated) : Component(associated) {
    scale.x = 1;
    scale.y = 1;
    currentFrame = 0;
    timeElapsed = 0;
    texture = nullptr;
}

Sprite::Sprite(GameObject& associated, string file, int frameCount,
            float frameTime, float secondsToSelfDestruct) : Sprite(associated) {

    Sprite::frameCount = frameCount;
    Sprite::frameTime = frameTime;
    Sprite::secondsToSelfDestruct = secondsToSelfDestruct;
    // cout << "frameCout: " << Sprite::frameCount << endl;
    // cout << "frameTime: " << Sprite::frameTime << endl;
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
        SetClip(0, 0, (width/frameCount), height);
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
    // cout << "widt div: " << width / frameCount << endl;
    return (width  * scale.x) / frameCount;
}
int Sprite::GetHeight() {
    return height * scale.y;
}

bool Sprite::IsOpen() {
    if (texture) {
        return true;
    } else {
        return false;
    }
}

void Sprite::Update(float dt) {

    timeElapsed += dt;
    if (frameCount > 1 && !selectOneFrame) {
        if(timeElapsed > frameTime) {
            timeElapsed = 0;
            if (currentFrame == frameCount) {
                currentFrame = 0;
            }
            SetFrame(currentFrame);
            currentFrame++;
        }
    }
    if (selectOneFrame) {
        SetFrame(oneFrame);
    }

    if (secondsToSelfDestruct > 0) {
        selfDestructCount.Update(dt);
        if (selfDestructCount.Get() > secondsToSelfDestruct) {
            associated.RequestDelete();
        }
    }
    
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

void Sprite::SetFrame(int frame) {
    currentFrame = frame;
    clipRect.x = (GetWidth() / scale.x) * currentFrame;
    // 101, 202, 303, 404, 505
    //clipRect.x = 101 * currentFrame;
    // cout << "clipRect X: " << clipRect.x << " width: " << GetWidth() << " h: " << GetHeight() << endl;
    // cout << "current Frame: " << currentFrame << " frame count:" << frameCount << endl << endl;
}

void Sprite::SetFrameCount(int frameCount) {
    Sprite::frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime) {
    Sprite::frameTime = frameTime;
}