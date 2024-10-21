#include <iostream>
#include "botdata.h"
#include "world.h"
#include "raylib.h"

Vector2 getForwardCoords(float x, float y, float rotation);

BotData::BotData(float x, float y, int width, int height, EntityType type, float rotation, World *world)
	: Entity(x, y, width, height, type, rotation)
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

	Vector2 coords = getForwardCoords(getX(), getY(), getRotation());

	setTargetX(coords.x);
	setTargetY(coords.y);
}

bool BotData::frontIsClear()
{
	Vector2 coords = getForwardCoords(getX(), getY(), getRotation());

	return world->isClear(coords.x, coords.y);
}

bool BotData::rightIsClear()
{
	Vector2 coords = getForwardCoords(getX(), getY(), ((int) getRotation() + 90) % 360);

	return world->isClear(coords.x, coords.y);
}

bool BotData::leftIsClear()
{
	int rotation = getRotation() - 90;

	if (rotation == -90)
		rotation = 270;

	Vector2 coords = getForwardCoords(getX(), getY(), rotation);

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

Vector2 getForwardCoords(float x, float y, float rotation)
{
	if (rotation == 0)
		return { x, y - tileSize };

	if (rotation == 90)
		return { x + tileSize, y };

	if (rotation == 180)
		return { x, y + tileSize };

	if (rotation == 270)
		return { x - tileSize, y };

	return { x, y };
}