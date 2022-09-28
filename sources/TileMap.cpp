#include "../headers/TileMap.h"
#include "../headers/Camera.h"
#include "../headers/InputManager.h"

void TileMap::Start() {
    cout << "start tileMap" << endl;
}

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {
    Load(file);
    SetTileSet(tileSet);
    // cout << "wid: " << tileSet->GetTileWidth() << endl;
    associated.box.w = (mapWidth - 1) * tileSet->GetTileWidth();
    associated.box.h = (mapHeight - 1) * tileSet->GetTileHeight();
}

void TileMap::Load(string file) {
    ifstream arq_map (file);
    string index;
    char c;
    int flag = 0;


    if(arq_map.is_open()) {
        while (arq_map.good()){
            arq_map.get(c);
            if (isdigit(c)) {
                index += c;
            } else {
                if (flag < 3) {
                    if (flag == 0) {
                        int w = stoi(index);
                        mapWidth = w;
                        index = "";
                    } else if (flag == 1) {
                        int h = stoi(index);
                        mapHeight = h;
                        index = "";
                    } else {
                        int d = stoi(index);
                        mapDepth = d;
                        index = "";
                    }
                    flag++;
                } else {
                    if (c == ',') {
                        int i = stoi(index);
                        //cout << i << " ";
                        tileMatrix.push_back(i - 1);
                    }
                    index = "";
                }
            }
        }

    } else {
        cout << "Erro ao abrir Arquivo texto TileMap" << endl;
    }
    arq_map.close();
    
    for (int i = 0; i < mapDepth; i++) {
        vetorLayerSpeed.push_back(make_pair(i, 1));
    }

    SetLayerSpeed(1, 1.2);
}

void TileMap::SetTileSet(TileSet* tileSet) {
    TileMap::tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    // x == 0
    // 2y + z = index
    // x != 0
    // (x+1) * numero de colunas + 2y + z
    int index;
    if (x == 0) {
        index = (2 * y) + z;
    } else {
        index = (x + 1) * mapWidth + (2 * y) + z;
    }
    return tileMatrix[index];
}

void TileMap::Render() {
    int layer;
    float speed;
    for(int i = 0; i < GetDepth(); i++) {
        layer = vetorLayerSpeed[i].first;
        speed = vetorLayerSpeed[i].second;
        // if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
        //     if(associated.box.Contem( InputManager::GetInstance().GetMouseX(), InputManager::GetInstance().GetMouseY() )) {
        //         cout << "mapa" << endl;
        //     }
        // }
        //cout << "Camera::pos.x: " << Camera::pos.x << " Camera::pos.y: " << Camera::pos.y << endl;
        RenderLayer(layer, speed, Camera::pos.x, Camera::pos.y);
    }
}

void TileMap::RenderLayer(int layer, float speed, float cameraX, float cameraY) {
    int area = GetWidth() * GetHeight();
    int num_tiles = area;
    //cout << "layer: " << layer << " speed: " << speed << endl;

    // cout << "area: " << area << endl; 
    int index = (layer * area);
    // cout << "index: " << index <<  " num_tiles: " << num_tiles << endl;
    int stop = index + num_tiles;
    // cout << "stop: " << stop << endl;
    while ( index < stop ) {
        for(int lin = 0; lin < GetHeight(); lin++) {
            
            for(int col = 0; col < GetWidth(); col++) {
                // cout << "lin: " << lin << " col: " << col << " index loop: " << index << " tile matrix 0: " << tileMatrix[index] << endl;
                tileSet->RenderTile(tileMatrix[index],( (col * tileSet->GetTileWidth()) - (cameraX * speed) ),(  (lin * tileSet->GetTileWidth()) - (cameraY * speed) ) );
                
                index++;
                
                
            }
        }
    }
    // associated.box.x = (cameraX) * tileSet->GetTileWidth();
    // associated.box.y = (cameraY) * tileSet->GetTileWidth();
    // cout << "layer x: " << associated.box.x << " y: " << associated.box.y << endl;
    
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(float dt) { }

bool TileMap::Is(string type) {
    string tileM = "TileMap";
    if (type == tileM){
        return true;
    } else {
        return false;
    }
}

void TileMap::SetLayerSpeed(int index, float speed) {
    get<1>(vetorLayerSpeed[index]) = speed;
}