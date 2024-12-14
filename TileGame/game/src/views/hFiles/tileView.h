#ifndef TILEVIEW_H
#define TILEVIEW_H

#include "tile.h"
#include "textures.h"
#include "raylib.h"
#include "entityView.h"
#include <map>

using namespace std;

class TileView: public EntityView {
    private:
        Tile* tile;
        Texture2D texture;
        Rectangle sourceRec;
        Vector2 dest;
        Color tint;
    public:
        TileView(Tile* tile);
        ~TileView();
        void tick();
        void draw(int vx, int vy, int vdx, int vdy, int vw, int vh);
        bool isViewFor(Entity* entity);

};

#endif 