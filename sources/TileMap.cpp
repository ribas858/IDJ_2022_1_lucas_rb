#include "../headers/TileMap.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {
    Load(file);
    TileMap::tileSet = tileSet;
    associated.box.x = 200;
    associated.box.y = 200;
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
    for(int deep = 0; deep < GetDepth(); deep++) {
        RenderLayer(deep);
    }
    
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {

    int area = (GetWidth() * GetHeight());
    int index = area * layer;
    int stop = index + area;
    while ( index < stop ) {
        for(int lin = 0; lin < GetHeight(); lin++) {
            for(int col = 0; col < GetWidth(); col++) {
                tileSet->RenderTile(tileMatrix[index], col * tileSet->GetTileWidth(), lin * tileSet->GetTileWidth());
                index++;
            }
        }
    }
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

void TileMap::Update(float dt) {
    
}

bool TileMap::Is(string type) {
    string tileM = "TileMap";
    if (type == tileM){
        return true;
    } else {
        return false;
    }
}