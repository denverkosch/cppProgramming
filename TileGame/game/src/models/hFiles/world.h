#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "entity.h"


struct PlayerActionMessage {
	Action action;
};


class World : public Subscriber {
    private:
        vector<Entity*> entities;
        vector<Entity*> collisions;
        vector<Entity*> deletions;
        Entity* player;

        void checkCollision(Entity* entity1, Entity* entity2);
    public:
        World();
        void clearWorld();
        void addEntity(Entity* entity);
        void addPlayer(Entity* entity);
        vector<Entity*> getEntities();
        Entity* getPlayer();
        void receiveMessage(string channel, string message, void* data);
        
        void tick();
};

#endif
