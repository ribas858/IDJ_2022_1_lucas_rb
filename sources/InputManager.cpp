#include "../headers/InputManager.h"

void InputManager::Update() {
    
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
    return false; // teste compile
}

InputManager& InputManager::GetInstance() {
    InputManager* test_compile;
    return *test_compile; // teste compile
}