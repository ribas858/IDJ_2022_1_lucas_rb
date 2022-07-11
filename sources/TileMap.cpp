#include "../headers/TileMap.h"

TileMap::TileMap(GameObject& associated, string file, TileSet* tileSet) : Component(associated) {}

void TileMap::Load(string file) {

}

void TileMap::SetTileSet(TileSet* tileSet) {

}

int& TileMap::At(int x, int y, int z) {
    int *a;
    return *a;
}

void TileMap::Render() {

}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {

}

int TileMap::GetWidth() {
    return 0;
}

int TileMap::GetHeight() {
    return 0;
}

int TileMap::GetDepth() {
    return 0;
}