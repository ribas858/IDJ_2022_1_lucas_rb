#include "../headers/State.h"
#include "../headers/Sprite.h"

#include "../headers/Face.h"
#include "../headers/Vec2.h"

#include "../headers/Sound.h"
#include "../headers/TileMap.h"



State::State() {
    quitRequested = false;
    cout << "State criado!!" << endl;

    GameObject* musica = new GameObject();
    music = new Music(*musica, "music/stageState.ogg");
    music->Play();

    music = new Music(*musica, "music/stageState.ogg");
    

    GameObject* background = new GameObject();
    bg = new Sprite(*background, "images/ocean.jpg");
    background->AddComponent(bg);
    objectArray.emplace_back(background);

    GameObject* map_obj = new GameObject();
    TileSet* tset = new TileSet(64, 64, "images/tileset.png");
    TileMap* tmap = new TileMap(*map_obj, "maps/tileMap.txt", tset);
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
    // if(SDL_QuitRequested()) {
    //     quitRequested = true;
    // }
    Input();

    for(int i=0; i<objectArray.size(); i++) {
        objectArray[i]->Update(0);
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
    Sprite* penguin = new Sprite(*gob, "images/penguinface.png");
    
    Sound* boom = new Sound(*gob, "sounds/boom.wav");
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
