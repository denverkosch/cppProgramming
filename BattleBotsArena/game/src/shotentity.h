#ifndef SHOTENTITY_H
#define SHOTENTITY_H

#include "entity.h"

class World;

const int shotWidth = 21;
const int shotHeight = 38;

class ShotEntity: public Entity
{
private:
	World* world;
	bool aboutToExplode = false;
	Entity* mySource;

	void tick();

public:
	ShotEntity(float x, float y, EntityType type, float rotation, World* world, Entity *mySource);

};

#endif
