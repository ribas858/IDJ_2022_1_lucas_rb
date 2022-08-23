#include "../headers/InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager instanceMg;
    return instanceMg;
}

void InputManager::Update() {
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent)) {
        // if (inputEvent.key.repeat) {
        //     cout << "repeat " << inputEvent.key.repeat << endl;
        // }
        
        if (!inputEvent.key.repeat) {

            if (inputEvent.type == SDL_KEYDOWN) {

                keyState[inputEvent.key.keysym.sym] = true;

                keyUpdate[inputEvent.key.keysym.sym] = updateCounter;

                //cout << "Tecla: " << inputEvent.key.keysym.sym << " - Frame: " << updateCounter << endl;
                
            }

            if (inputEvent.type == SDL_KEYUP) {
                keyState[inputEvent.key.keysym.sym] = false;
                keyUpdate[inputEvent.key.keysym.sym] = updateCounter;

                //cout << "Tecla solta: " << inputEvent.key.keysym.sym << " - Frame: " << updateCounter << endl;
            }

            if (inputEvent.type == SDL_MOUSEBUTTONDOWN) {
                if (inputEvent.button.button == SDL_BUTTON_LEFT) {
                    mouseState[1] = true;
                    mouseUpdate[1] = updateCounter;
                    //cout << "mouse: " <<  "Esquerdo - Frame: " << updateCounter << endl;
                }
                else if (inputEvent.button.button == SDL_BUTTON_MIDDLE) {
                    mouseState[2] = true;
                    mouseUpdate[2] = updateCounter;
                    //cout << "mouse: " <<  "Meio - Frame: " << updateCounter << endl;
                }
                else if (inputEvent.button.button == SDL_BUTTON_RIGHT) {
                    mouseState[3] = true;
                    mouseUpdate[3] = updateCounter;
                    //cout << "mouse: " <<  "Direito - Frame: " << updateCounter << endl;
                }
                else if (inputEvent.button.button == SDL_BUTTON_X1) {
                    mouseState[4] = true;
                    mouseUpdate[4] = updateCounter;
                    //cout << "mouse: " <<  "x1 - Frame: " << updateCounter << endl;
                }
                else if (inputEvent.button.button == SDL_BUTTON_X2) {
                    mouseState[5] = true;
                    mouseUpdate[5] = updateCounter;
                    //cout << "mouse: " <<  "x2 - Frame: " << updateCounter << endl;
                }
            }

            if (inputEvent.type == SDL_MOUSEBUTTONUP) {
                if (inputEvent.button.button == SDL_BUTTON_LEFT) {
                    mouseState[1] = false;
                    mouseUpdate[1] = updateCounter;
                    //cout << "mouse solta:" <<  "Esquerdo - Frame: " << updateCounter << endl;
                }
                else if (inputEvent.button.button == SDL_BUTTON_MIDDLE) {
                    mouseState[2] = false;
                    mouseUpdate[2] = updateCounter;
                    //cout << "mouse solta:" <<  "Meio - Frame: " << updateCounter << endl;
                }
                else if (inputEvent.button.button == SDL_BUTTON_RIGHT) {
                    mouseState[3] = false;
                    mouseUpdate[3] = updateCounter;
                    //cout << "mouse solta:" <<  "Direito - Frame: " << updateCounter << endl;
                }
                else if (inputEvent.button.button == SDL_BUTTON_X1) {
                    mouseState[4] = false;
                    mouseUpdate[4] = updateCounter;
                    //cout << "mouse solta:" <<  "x1 - Frame: " << updateCounter << endl;
                }
                else if (inputEvent.button.button == SDL_BUTTON_X2) {
                    mouseState[5] = false;
                    mouseUpdate[5] = updateCounter;
                    //cout << "mouse solta:" <<  "x2 - Frame: " << updateCounter << endl;
                }
            }

            if (inputEvent.type == SDL_QUIT) {
                quitRequested = true;
            }
        }
    }
    // updateCounter++;
    //cout << "Update Counter: " << updateCounter << endl;
}

bool InputManager::KeyPress(int key) {
    if (FindKey(key)) {
        if (keyState.find(key)->second) {
            //cout << "Update Counter key: " << updateCounter << endl;
            if (keyUpdate.find(key)->second == updateCounter) {
                // cout << "key: " << key << " update:" << keyUpdate.find(key)->second << " ";
                // cout << "Frame: " << updateCounter << endl << endl;
                return true;
            }
        } 
        
    }
    return false;
}

bool InputManager::KeyRelease(int key) {
    if (FindKey(key)) {
        if (!keyState.find(key)->second) {
            if (keyUpdate.find(key)->second == updateCounter) {
                // cout << "key: " << key << " update solte:" << keyUpdate.find(key)->second << " ";
                // cout << "Frame: " << updateCounter << endl;
                return true;
            }
        }
    }
    return false; // teste compile
}

bool InputManager::IsKeyDown(int key) {
    // if (FindKey(key)) {
    //     return keyState.find(key)->second;
    // }
    return false; // teste compile
}

bool InputManager::MousePress(int button) {
    for (int i = 1; i < 6; i++) {
        if (i == button) {
            if(mouseState[i]) {
                if (mouseUpdate[i] == updateCounter) {
                    // cout << "mouse: " << button << " update solte:" << mouseUpdate[i] << " ";
                    // cout << "Frame: " << updateCounter << endl << endl;
                    return true;
                }
            }
        }
    }
    return false; // teste compile
}

bool InputManager::MouseRelease(int button) {
    return false; // teste compile
}

bool InputManager::IsMouseDown(int button) {
    // for (int i = 1; i < 6; i++) {
    //     if (mouseState[i] == button) {
    //         return true;
    //     }
    // }
    return false;
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}

bool InputManager::FindKey(int key) {
    if (keyState.find(key) == keyState.end()) {
        return false;
    } else {
        return true;
    }
}