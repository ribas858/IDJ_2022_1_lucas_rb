#ifndef TILEMAP_H
#define TILEMAP_H

#include "../headers/GameObject.h"
#include "../headers/TileSet.h"
#include "../headers/Vec2.h"


class TileMap : public Component {
    public:
        TileMap(GameObject& associated, string file, TileSet* tileSet);
        void Load(string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        
        void RenderLayer(int layer, float speed, float cameraX, float cameraY);
        int GetWidth();
        int GetHeight();
        int GetDepth();

        void Render() override;
        void Update(float dt) override;
        bool Is(string type) override;
        void Start() override;

        void SetLayerSpeed(int index, float speed);

    private:
        vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;
        vector<pair <int, float>> vetorLayerSpeed;
};

#endif