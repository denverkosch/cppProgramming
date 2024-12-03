#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "entity.h"

class World;

class ExplosionEntity: public Entity
{
private:
	World* world;

	void animationDone();

public:
	ExplosionEntity(float x, float y, EntityType type, float rotation, World* world);

};

#endif
