#include "entitydata.h"

EntityData::EntityData(Entity* entity)
{
	this->entity = entity;
}

float EntityData::getX()
{
	return entity->getX();
}

float EntityData::getY()
{
	return entity->getY();
}

EntityType EntityData::getType()
{
	return entity->getType();
}

float EntityData::getRotation()
{
	return entity->getRotation();
}

int EntityData::getWidth()
{
	return entity->getWidth();
}

int EntityData::getHeight()
{
	return entity->getHeight();
}

bool EntityData::sameEntity(Entity* other)
{
	return entity == other;
}

int EntityData::getRow()
{
	int y = getY();
	
	return y / tileSize;
}

int EntityData::getCol()
{
	int x = getX();
	
	return x / tileSize;
}
