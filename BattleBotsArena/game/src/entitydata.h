#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "entity.h"

class EntityData
{
private:
	Entity* entity;

public:
	EntityData(Entity *entity);

	float getX();
	float getY();
	int getRow();
	int getCol();
	int getWidth();
	int getHeight();
	EntityType getType();
	float getRotation();

	bool sameEntity(Entity* other);

};

#endif
