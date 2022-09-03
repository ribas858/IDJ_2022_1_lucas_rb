#ifndef TILEMAP_H
#define TILEMAP_H

#include "../headers/GameObject.h"
#include "../headers/TileSet.h"

class TileMap : public Component {
    public:
        TileMap(GameObject& associated, string file, TileSet* tileSet);
        void Load(string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        
        void RenderLayer(int layer, float cameraX, float cameraY);
        int GetWidth();
        int GetHeight();
        int GetDepth();

        void Render() override;
        void Update(float dt) override;
        bool Is(string type) override;

    private:
        vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
};

#endif