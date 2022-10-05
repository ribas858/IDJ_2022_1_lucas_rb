#include "../headers/InputManager.h"
#include "../headers/Camera.h"


InputManager& InputManager::GetInstance() {
    static InputManager instanceMg;
    return instanceMg;
}

void InputManager::Update() {
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;

    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent)) {
        
        if (!inputEvent.key.repeat) {

            if (inputEvent.type == SDL_KEYDOWN) {
                keyState[inputEvent.key.keysym.sym] = true;
                keyUpdate[inputEvent.key.keysym.sym] = updateCounter;
            }

            if (inputEvent.type == SDL_KEYUP) {
                keyState[inputEvent.key.keysym.sym] = false;
                keyUpdate[inputEvent.key.keysym.sym] = updateCounter;
            }

            if (inputEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (inputEvent.button.button == LEFT_MOUSE_BUTTON) {
                    mouseState[1] = true;
                    mouseUpdate[1] = updateCounter;
                }
                else if (inputEvent.button.button == SDL_BUTTON_MIDDLE) {
                    mouseState[2] = true;
                    mouseUpdate[2] = updateCounter;
                }
                else if (inputEvent.button.button == SDL_BUTTON_RIGHT) {
                    mouseState[3] = true;
                    mouseUpdate[3] = updateCounter;
                }
                else if (inputEvent.button.button == SDL_BUTTON_X1) {
                    mouseState[4] = true;
                    mouseUpdate[4] = updateCounter;
                }
                else if (inputEvent.button.button == SDL_BUTTON_X2) {
                    mouseState[5] = true;
                    mouseUpdate[5] = updateCounter;
                }
            }

            if (inputEvent.type == SDL_MOUSEBUTTONUP) {
                if (inputEvent.button.button == LEFT_MOUSE_BUTTON) {
                    mouseState[1] = false;
                    mouseUpdate[1] = updateCounter;
                }
                else if (inputEvent.button.button == SDL_BUTTON_MIDDLE) {
                    mouseState[2] = false;
                    mouseUpdate[2] = updateCounter;
                }
                else if (inputEvent.button.button == SDL_BUTTON_RIGHT) {
                    mouseState[3] = false;
                    mouseUpdate[3] = updateCounter;
                }
                else if (inputEvent.button.button == SDL_BUTTON_X1) {
                    mouseState[4] = false;
                    mouseUpdate[4] = updateCounter;
                }
                else if (inputEvent.button.button == SDL_BUTTON_X2) {
                    mouseState[5] = false;
                    mouseUpdate[5] = updateCounter;
                }
            }

            if (inputEvent.type == SDL_QUIT) {
                quitRequested = true;
            }
        }
    }
}

/////////////////////////////////////////////
///////////////////////////////////// PRESS

bool InputManager::KeyPress(int key) {
    
    if (FindKey(key)) {
        if (keyState.find(key)->second) {
            if (keyUpdate.find(key)->second == updateCounter) {
                return true;
            }
        } 
        
    }
    return false;
}

bool InputManager::MousePress(int button) {
    
    for (int i = 1; i < 6; i++) {
        if (i == button) {
            if(mouseState[i]) {
                if (mouseUpdate[i] == updateCounter) {
                    return true;
                }
            }
        }
    }
    return false; // teste compile
}

///////////////////////////////////// RELEASE

bool InputManager::KeyRelease(int key) {
    if (FindKey(key)) {
        if (!keyState.find(key)->second) {
            if (keyUpdate.find(key)->second == updateCounter) {
                return true;
            }
        }
    }
    return false; // teste compile
}

bool InputManager::MouseRelease(int button) {
    for (int i = 1; i < 6; i++) {
        if (i == button) {
            if(!mouseState[i]) {
                if (mouseUpdate[i] == updateCounter) {
                    return true;
                }
            }
        }
    }
    return false; // teste compile
}

///////////////////////////////////// IS DOWN

bool InputManager::IsKeyDown(int key) {
    if (FindKey(key)) {
        while (keyState.find(key)->second) {
            return true;
        }
    }
    return false; // teste compile
}

bool InputManager::IsMouseDown(int button) {
    for (int i = 1; i < 6; i++) {
        if (i == button) {
            while (mouseState[i]) {
                return true;
            }
        }
    }
    return false;
}

/////////////////////////////////////////////

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

///////////////////////////////////// EXTRA

bool InputManager::FindKey(int key) {
    if (keyState.find(key) == keyState.end()) {
        return false;
    } else {
        return true;
    }
}

const int& InputManager::GetUpdateCounter() const {
    return updateCounter;
}

int& InputManager::SetUpdateCounter() {
    return updateCounter;
}

const int& InputManager::GetLastFrame() const {
    return lastFrame;
}

int& InputManager::SetLastFrame() {
    return lastFrame;
}

vector<int>* InputManager::GetLoadMinions() {
    return &loadMinions;
}

void InputManager::SetLoadMinions(int id) {
    if (!loadMinions.empty()) {
        loadMinions.at(id)++;
    }
}