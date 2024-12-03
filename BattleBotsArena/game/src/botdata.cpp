#include <iostream>
#include "botdata.h"
#include "world.h"
#include "utility.h"
#include "shotentity.h"

BotData::BotData(float x, float y, int width, int height, EntityType type, float rotation, World *world)
	: Entity(x, y, width, height, type, rotation, true)
{
	this->world = world;
}

void BotData::turnLeft()
{
	if (doingAction)
		return;

	doingAction = true;

	if (getRotation() == 0)
	{
		setRotation(360);
		setTargetRotation(270);
	}
	else
		setTargetRotation(getRotation() - 90);
}

void BotData::turnRight()
{
	if (doingAction)
		return;

	doingAction = true;

	if (getRotation() == 360)
	{
		setRotation(0);
		setTargetRotation(90);
	}
	else
		setTargetRotation(getRotation() + 90);
}

void BotData::move()
{
	if (doingAction)
		return;

	doingAction = true;

	if (!frontIsClear())
		return;

	Vector2 coords = getForwardCoords(getX(), getY(), getRotation(), tileSize);

	setTargetX(coords.x);
	setTargetY(coords.y);
}

bool BotData::frontIsClear()
{
	Vector2 coords = getForwardCoords(getX(), getY(), getRotation(), tileSize);

	return world->isClear(coords.x, coords.y);
}

bool BotData::rightIsClear()
{
	Vector2 coords = getForwardCoords(getX(), getY(), ((int) getRotation() + 90) % 360, tileSize);

	return world->isClear(coords.x, coords.y);
}

bool BotData::leftIsClear()
{
	int rotation = getRotation() - 90;

	if (rotation == -90)
		rotation = 270;

	Vector2 coords = getForwardCoords(getX(), getY(), rotation, tileSize);

	return world->isClear(coords.x, coords.y);
}

bool BotData::amOnExit()
{
	return world->isOnExit(getX(), getY());
}

bool BotData::facingNorth()
{
	return getRotation() == 0;
}

bool BotData::facingSouth()
{
	return getRotation() == 180;
}

bool BotData::facingEast()
{
	return getRotation() == 90;
}

bool BotData::facingWest()
{
	return getRotation() == 270;
}

void BotData::tick()
{
	doingAction = false;
	Entity::tick();
}

EntityData BotData::scan()
{
	return world->scan(getX(), getY(), getRotation());
}

void BotData::fire()
{
	if (doingAction)
		return;

	if (!canFire())
		return;

	// Need to calculate where the shot is created.  Visually it should
	// look like it's being fired from the barrel of the tank.
	int shotX = getX();
	int shotY = getY();

	if (getRotation() == 0)
	{
		shotX += tileSize / 2 - shotWidth / 2;
		shotY -= shotHeight / 2;
	}

	if (getRotation() == 90)
	{
		shotX += tileSize - shotWidth / 2;
		shotY += tileSize / 2 - shotHeight / 2;
	}

	if (getRotation() == 180)
	{
		shotX += tileSize / 2 - shotWidth / 2;
		shotY += tileSize - shotHeight / 2;
	}

	if (getRotation() == 270)
	{
		shotX -= shotWidth / 2;
		shotY += tileSize / 2 - shotHeight / 2;
	}
	
	shot = new ShotEntity(shotX, shotY, TankShot, getRotation(), world, this);
	world->addEntity(shot);
}

bool BotData::canFire()
{
	// If we haven't fired yet, we can fire
	if (shot == NULL)
		return true;

	// If we have fired, and the shot is still in the world, we cannot fire
	if (world->entityExists(shot))
		return false;

	// We have fired, and the shot is not in the world.  Clean it up.
	shot = NULL;

	return true;
}

int BotData::getHealth()
{
	return Entity::getHealth();
}

void BotData::setTag(char *t)
{
	return Entity::setTag(t);
}

int BotData::getRow()
{
	int y = getY();
	
	return y / tileSize;
}

int BotData::getCol()
{
	int x = getX();
	
	return x / tileSize;
}
