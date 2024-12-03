#include <iostream>
#include "shotentity.h"
#include "explosion.h"
#include "world.h"
#include "utility.h"

const int shotSpeed = 2;

ShotEntity::ShotEntity(float x, float y, EntityType type, float rotation, World* world, Entity* mySource)
	: Entity(x, y, shotWidth, shotHeight, type, rotation)
{
	this->world = world;
	this->mySource = mySource;
}

void ShotEntity::tick()
{
	// Don't call Entity::tick() since tank shots work differently than other entities
	// Entity::tick();

	// Calculate the tile coordinates for the shot.
	int tileX = (((int)getX()) / tileSize) * tileSize;
	int tileY = (((int)getY()) / tileSize) * tileSize;

	if (aboutToExplode)
	{
		// Add an explosion entity to the world in the current tile
		ExplosionEntity* explosion = new ExplosionEntity(tileX, tileY, Explosion, 0, world);
		world->addEntity(explosion);

		// Do damage to affected entities
		world->shotHits(this, 40, mySource);

		// Remove ourself from the world
		world->removeEntity(this);

		return;
	}

	// Move the shot forward
	Vector2 coords = getForwardCoords(getX(), getY(), getRotation(), shotSpeed);
	setX(coords.x);
	setY(coords.y);

	// See if we are in the same tile as something other than a tank shot
	vector<EntityData> entities = world->inSameTile(tileX, tileY);

	for (EntityData entity : entities)
	{
		if (entity.getType() != TankShot && ! entity.sameEntity(mySource))
		{
			aboutToExplode = true;
			break;
		}
	}
}
