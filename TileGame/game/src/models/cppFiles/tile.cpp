#include "tile.h"

Tile::Tile(float x, float y, int width, int height, EntitySpecific tile, bool passable) : Entity(x, y, width, height, TERRAIN, tile) {
    this->passable = passable;
}

Tile::~Tile() {}

void Tile::tick() {
    // Do nothing
}


bool Tile::isPassable() {
    return passable;
}

void Tile::setPassable(bool passable) {
    this->passable = passable;
}

void Tile::receiveMessage(string channel, string message, void* data) {
    // Do nothing
}