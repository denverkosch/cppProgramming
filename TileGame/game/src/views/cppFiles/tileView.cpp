#include "tile.h"
#include "tileView.h"
#include "entityView.h"
#include "textures.h"
#include "raylib.h"
#include <map>
#include <iostream>

using namespace std;

map<EntitySpecific, string> tileMapping = {
    {FLOOR, "resources/spritesheets/WorldTiles/floor.png"},
    {PLATFORM, "resources/spritesheets/WorldTiles/platform.png"},
    {WALL, "resources/spritesheets/WorldTiles/wall.png"},
};

TileView::TileView(Tile* tile) : EntityView(tile) {
    this->tile = tile;
    texture = Textures::loadTexture(tileMapping[tile->getSpecific()]);
    sourceRec = {0, 0, 32.0, 32.0};
    dest = {tile->getX(), tile->getY()};
    tint = WHITE;
}

TileView::~TileView() {
    UnloadTexture(texture);
}

void TileView::tick() {
    dest.x = tile->getX();
    dest.y = tile->getY();
}

void TileView::draw(int vx, int vy, int vdx, int vdy, int vw, int vh) {
    Vector2 screenPosition = {
        dest.x - vx + vdx,
        dest.y - vy + vdy
    };
    DrawTextureRec(texture, sourceRec, screenPosition, WHITE);
}

bool TileView::isViewFor(Entity* entity) {
    return entity == tile;
}