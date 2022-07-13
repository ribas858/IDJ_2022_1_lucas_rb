#include "../headers/TileSet.h"
#include "../headers/Sprite.h"
#include "../headers/Game.h"


TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileWidth(tileWidth), tileHeight(tileHeight) {
    GameObject* sp_tile = new GameObject();
    tileSet = new Sprite(*sp_tile, file);
    
    if (tileSet){
        // c = w / tw
        // l = h / th
        columns = tileSet->GetWidth() / tileWidth;
        rows = tileSet->GetHeight() / tileHeight;
    }
}

TileSet::~TileSet() {
    delete tileSet;
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    int la, ca, xct, yct;
    int num_tiles = rows * columns;
    //cout << "num_tile:" << num_tiles << " | linhas:" << rows << " | columns:" << columns << endl;
    if (index >= 0 && index < num_tiles) {
        // LA = I / C
        // CA = I - (LA * C)
        // Xct = TW * CA
        // Yct = TH * LA
        la = index / columns;
        ca = index - (la * columns);
        xct = tileWidth * ca;
        yct = tileHeight * la;

        //cout << "la: " << la << " ca: " << ca << " xct:" << xct << " yct:" << yct << endl;
        tileSet->SetClip(xct, yct, tileWidth, tileHeight);
       
        tileSet->Render(x, y);

    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}