#ifndef TILESET_H
#define TILESET_H

#include "../headers/base_includes.h"

class TileSet {
    public:
        TileSet(int tileWidth, int tileHeight, string file);
        void RenderTile(unsigned index, float x, float y);

        ~TileSet();

        int GetTileWidth();
        int GetTileHeight();

    private:
        class Sprite* tileSet;
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;
};

#endif