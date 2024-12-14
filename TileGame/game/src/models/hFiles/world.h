#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "entity.h"
#include "tile.h"


struct PlayerActionMessage {
	Action action;
};


class World : public Subscriber {
    private:
        vector<Entity*> entities;
        vector<Tile*> tiles;
        vector<Entity*> collisions;
        vector<Entity*> deletions;
        Entity* player;

        void checkCollision(Entity* entity1, Entity* entity2);
    public:
        World();
        void clearWorld();
        void addEntity(Entity* entity);
        void addTile(Tile* tile);
        void addPlayer(Entity* entity);
        vector<Entity*> getEntities();
        vector<Tile*> getTiles();
        Entity* getPlayer();
        void receiveMessage(string channel, string message, void* data);
        
        void tick();
};

#endif
