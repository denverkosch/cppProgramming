#ifndef TILE_H
#define TILE_H

#include "entity.h"

class Tile : public Entity {
    private:
        bool passable;
    public:
        Tile(float x, float y, int width, int height, EntitySpecific skin, bool passable);
        ~Tile();
        void tick();
        bool isPassable();
        void setPassable(bool passable);
        void receiveMessage(string channel, string message, void* data);
};

#endif