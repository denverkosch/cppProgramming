#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "entity.h"
#include "pubsub.h"
#include "botdata.h"

using namespace std;

class World: public Subscriber
{
private:
	vector<Entity*> entities;
	vector<Entity*> collisions;
	vector<Entity*> deletions;

	void processShotHit(int damage, Entity* entity, vector<Entity*> &toRemove);
	bool doesShotHit(Entity* shot, Entity* entity);

public:
	World();
	void clearWorld();
	vector<BotData *> initWorld(int width, int height, int numBots);
	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	bool entityExists(Entity* entity);

	bool isClear(int x, int y);
	bool isOnExit(int x, int y);
	EntityData scan(int x, int y, int rotation);
	vector<EntityData> inSameTile(int x, int y);
	void shotHits(ShotEntity* shot, int damage, Entity *source);

	void tick();
	void receiveMessage(string channel, string message, void* data);
};

#endif
