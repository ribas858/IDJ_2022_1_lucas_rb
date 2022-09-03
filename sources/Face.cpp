#include "../headers/Face.h"
#include "../headers/Sound.h"
#include "../headers/Game.h"
#include "../headers/InputManager.h"
#include "../headers/Camera.h"

Face::Face(GameObject& associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage (int damage){
    cout << "Hitpoints: " << hitpoints << endl;
    hitpoints -= damage;
    if (hitpoints <= 0){
        Component* cp = associated.GetComponent("Sound"); 
        if (cp) {
            Sound* som = (Sound*)cp;
            // som->Play();
            //cout << "BOOMMMMM..." << endl;
        }
        
        SDL_RenderClear(Game::GetInstance().GetRenderer());
        associated.RequestDelete();
    }
    cout << "Hitpoints apos dano: " << hitpoints << endl << endl;
}

void Face::Update(float dt) {
    
}

void Face::Update(vector<unique_ptr<GameObject>>& objectArray) {
    
    if(InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        cout << "face attack" << endl;
        Face* face = nullptr;
        for(int i = objectArray.size() - 1; i >= 0; --i) {

            float mouseX = (float)InputManager::GetInstance().GetMouseX();
            float mouseY = (float)InputManager::GetInstance().GetMouseY();
            cout << "FACE mouseX: " << mouseX << " FACE mouseY: " << mouseY << endl;

            if(objectArray[i]->box.Contem( mouseX, mouseY )) {
                face = (Face*) objectArray[i]->GetComponent("Face");
                if (face != nullptr) {
                    cout << "face attack invest" << endl;
                    break;
                }
            }
        }
        ostringstream endereco_face; 
        endereco_face << face;
        cout << "set lastAdr: " << InputManager::GetInstance().GetLastAdressFace() << endl;
        if (InputManager::GetInstance().GetLastAdressFace().empty() && face != nullptr) {
            cout << "atribuiu" << endl;
            InputManager::GetInstance().SetLastAdressFace() = endereco_face.str();
            
        }
        
        cout << "face: " << face << " lastAdr: " << InputManager::GetInstance().GetLastAdressFace() << " adr face: " << endereco_face.str() << endl;
        cout << "Update counter: " << InputManager::GetInstance().GetUpdateCounter() << " last frame: " << InputManager::GetInstance().GetLastFrame() << endl << endl;
        if (face != nullptr && (
                InputManager::GetInstance().GetUpdateCounter() != InputManager::GetInstance().GetLastFrame()) ) {
            
            int aux = rand() % 10 + 10;
            // cout << "Dano: " << aux << " obj: " << face << endl;
            face->Damage(aux);
            
            
        }
        if (face != nullptr) {
            InputManager::GetInstance().SetLastAdressFace() = endereco_face.str();
        }
        InputManager::GetInstance().SetLastFrame() = InputManager::GetInstance().GetUpdateCounter();
        //cout << "obj: " << endereco_face.str() << endl;
        // cout << endl;
    }
}

void Face::Render() {
    // cout << "render face" << endl;
}

bool Face::Is(string type) {
    string face = "Face";
    if (type == face){
        return true;
    } else {
        return false;
    }
}