#include "../headers/State.h"
#include "../headers/Sprite.h"

#include "../headers/Face.h"
#include "../headers/Vec2.h"

#include "../headers/Sound.h"
#include "../headers/TileMap.h"

#include "../headers/InputManager.h"


State::State() : music("resources/music/stageState.ogg"){
    quitRequested = false;
    cout << "State criado!!" << endl;

    music.Play();
    

    GameObject* background = new GameObject();
    bg = new Sprite(*background, "resources/images/ocean.jpg");
    background->AddComponent(bg);
    objectArray.emplace_back(background);

    GameObject* map_obj = new GameObject();
    TileSet* tset = new TileSet(64, 64, "resources/images/tileset.png");
    TileMap* tmap = new TileMap(*map_obj, "resources/maps/tileMap.txt", tset);
    map_obj->AddComponent(tmap);
    objectArray.emplace_back(map_obj);

}

State::~State() {
    objectArray.clear();
}

bool State::QuitRequested() {
    return quitRequested;
}

void State::LoadAssets() {}

void State::Update(float dt) {
    if(InputManager::GetInstance().QuitRequested() || InputManager::GetInstance().KeyPress(SDLK_ESCAPE)) {
        music.~Music();
        quitRequested = true;
    }

    if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
        float PI = 3.14159;
        Vec2 objPos = Vec2(200, 0).Rotate( -PI + PI*(rand() % 1001)/500.0 ).Soma(Vec2
            ( InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY() ));

        AddObject((int)objPos.x, (int)objPos.y);
    }
    
    //InputManager::GetInstance().MousePress(SDL_BUTTON_LEFT);
    // cout << objectArray.size() << endl;
    
    for(int i=0; i<objectArray.size(); i++) {
        if (objectArray[i]->GetComponent("Face")) {
            Face* face = (Face*) objectArray[i]->GetComponent("Face");
            face->Update(objectArray);
        } else {
            if(!objectArray[i]->GetComponent("Face")) {
                objectArray[i]->Update(0);
            }
        }
    }
    
    for(int i=0; i<objectArray.size(); i++) {
        if(objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
            cout << "limpa no objectArray" << endl << endl;
        }
    }
}

void State::Render() {
    for (vector<unique_ptr<GameObject>>::iterator ob = objectArray.begin(); ob != objectArray.end(); ob++) {
        (*ob)->Render();
    }
}



void State::AddObject(int mouseX, int mouseY) {
    GameObject* gob = new GameObject();
    Sprite* penguin = new Sprite(*gob, "resources/images/penguinface.png");
    
    Sound* boom = new Sound(*gob, "resources/sounds/boom.wav");
    Face* logk = new Face(*gob);

    gob->box.x = mouseX;
    gob->box.y = mouseY;
    gob->AddComponent(penguin);
    gob->AddComponent(boom);
    gob->AddComponent(logk);


    objectArray.emplace_back(gob);

}


void State::Input() {
	SDL_Event event;
	int mouseX, mouseY;
    float PI = 3.14159;

	// Obtenha as coordenadas do mouse
	SDL_GetMouseState(&mouseX, &mouseY);
    //cout << "Mouse X: " << mouseX;
    //cout << " Mouse Y: " << mouseY << endl;

	// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
	while (SDL_PollEvent(&event)) {

		// Se o evento for quit, setar a flag para terminação
		if(event.type == SDL_QUIT) {
            music.~Music();
			quitRequested = true;
		}
		
		//Se o evento for clique...
		if(event.type == SDL_MOUSEBUTTONDOWN) {

			// Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
			for(int i = objectArray.size() - 1; i >= 0; --i) {
				// Obtem o ponteiro e casta pra Face.
				GameObject* go = (GameObject*) objectArray[i].get();
				// Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
				// O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
				// ao usar get(), violamos esse princípio e estamos menos seguros.
				// Esse código, assim como a classe Face, é provisório. Futuramente, para
				// chamar funções de GameObjects, use objectArray[i]->função() direto.
                
				if(go->box.Contem((float)mouseX, (float)mouseY)) {
					Face* face = (Face*)go->GetComponent("Face");
                    
					if (face != nullptr ) {
                        //cout << "É inimigo.. Destroyyyy" << endl;
						// Aplica dano
						face->Damage(std::rand() % 10 + 10);
						// Sai do loop (só queremos acertar um)
						break;
					} else {
                        cout << "Não é inimigo" << endl;
                    }
				}
			}
		}
		if( event.type == SDL_KEYDOWN ) {
			// Se a tecla for ESC, setar a flag de quit
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
                music.~Music();
				quitRequested = true;
			}
			// Se não, crie um objeto
			else {
				Vec2 objPos = Vec2(200, 0).Rotate( -PI + PI*(rand() % 1001)/500.0 ).Soma(Vec2( mouseX, mouseY ));
                // cout << "objPos.x: " << objPos.x;
                // cout << " objPos.y: " << objPos.y << endl;
				AddObject((int)objPos.x, (int)objPos.y);
                //AddObject(300, 300);
			}
		}
	}
}
