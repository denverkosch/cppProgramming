#include <iostream>
#include "explosion.h"
#include "world.h"

const int shotSpeed = 2;

ExplosionEntity::ExplosionEntity(float x, float y, EntityType type, float rotation, World* world)
	: Entity(x, y, tileSize, tileSize, type, rotation)
{
	this->world = world;
	setNeedAnimated(true);
}

void ExplosionEntity::animationDone()
{
	world->removeEntity(this);
}