#include "../headers/InputManager.h"

InputManager& InputManager::GetInstance() {
    static InputManager iMgInstance;
    return iMgInstance;
}

void InputManager::Update() {
    SDL_Event inputEvent;
    while (SDL_PollEvent(&inputEvent)) {

        if (inputEvent.type == SDL_KEYDOWN) {
            cout << "quit r" << quitRequested << endl; 
            // Se a tecla for ESC, setar a flag de quit
			if( inputEvent.key.keysym.sym == SDLK_ESCAPE ) {
				quitRequested = true;
			}
            
        }

        if (inputEvent.type == SDL_KEYUP) {
            
        }

        if (inputEvent.type == SDL_MOUSEBUTTONDOWN) {
            if (inputEvent.button.button == SDL_BUTTON_LEFT) {
                mouseState[2] = true;
                cout << "mouse: " <<  "Esquerdo" << endl;
            }
            else if (inputEvent.button.button == SDL_BUTTON_MIDDLE) {
                // mouseState[2] = true;
                cout << "mouse: " <<  "Meio" << endl;
            }
            else if (inputEvent.button.button == SDL_BUTTON_RIGHT) {
                // mouseState[3] = true;
                cout << "mouse: " <<  "Direito" << endl;
            }
            else if (inputEvent.button.button == SDL_BUTTON_X1) {
                // mouseState[4] = true;
                cout << "mouse: " <<  "x1" << endl;
            }
            else if (inputEvent.button.button == SDL_BUTTON_X2) {
                // mouseState[5] = true;
                cout << "mouse: " <<  "x2" << endl;
            }
        }

        if (inputEvent.type == SDL_MOUSEBUTTONUP) {
            // if (inputEvent.button.button == SDL_BUTTON_LEFT) {
            //     mouseState[1] = false;
            //     cout << "mouse solta:" <<  "Esquerdo" << endl;
            // }
            // else if (inputEvent.button.button == SDL_BUTTON_MIDDLE) {
            //     mouseState[2] = false;
            //     cout << "mouse solta:" <<  "Meio" << endl;
            // }
            // else if (inputEvent.button.button == SDL_BUTTON_RIGHT) {
            //     mouseState[3] = false;
            //     cout << "mouse solta:" <<  "Direito" << endl;
            // }
            // else if (inputEvent.button.button == SDL_BUTTON_X1) {
            //     mouseState[4] = false;
            //     cout << "mouse solta:" <<  "x1" << endl;
            // }
            // else if (inputEvent.button.button == SDL_BUTTON_X2) {
            //     mouseState[5] = false;
            //     cout << "mouse solta:" <<  "x2" << endl;
            // }
        }

        if (inputEvent.type == SDL_QUIT) {
            quitRequested = true;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return false; // teste compile
}

bool InputManager::KeyRelease(int key) {
    return false; // teste compile
}

bool InputManager::IsKeyDown(int key) {
    return false; // teste compile
}

bool InputManager::MousePress(int button) {
    return false; // teste compile
}

bool InputManager::MouseRelease(int button) {
    return false; // teste compile
}

bool InputManager::IsMouseDown(int button) {
    return false; // teste compile
}

int InputManager::GetMouseX() {
    return 1; // teste compile
}

int InputManager::GetMouseY() {
    return 1; // teste compile
}

bool InputManager::QuitRequested() {
    return quitRequested;
}