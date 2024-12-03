#include <iostream>
#include <algorithm>
#include "entity.h"

// We need to complete the animation sooner to allow
// for inconsistencies in the frames per second measurement
const int ticksToAdjust = ticksPerTurn - 10;

Entity::Entity(float x, float y, int width, int height, EntityType type, float rotation, bool vulnerable)
{
	this->x = x;
	this->y = y;
	this->rotation = rotation;
	this->targetX = x;
	this->targetY = y;
	this->targetRotation = rotation;
	this->width = width;
	this->height = height;
	this->type = type;
	this->needsAnimated = false;
	this->tickCounter = -1;
	this->adjustAmount = 0;
	this->vulnerable = vulnerable;
	this->tag = "";
}

char *Entity::getTag()
{
	return tag;
}

void Entity::setTag(char *t)
{
	tag = t;
}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

int Entity::getWidth()
{
	return width;
}

int Entity::getHeight()
{
	return height;
}

void Entity::setX(float x)
{
	this->x = x;
}

void Entity::setY(float y)
{
	this->y = y;
}

void Entity::setTargetX(float x)
{
	if (this->x != x)
	{
		this->targetX = x;
		tickCounter = ticksToAdjust;
		adjustAmount = (x - this->x) / ticksToAdjust;
	}
}

void Entity::setTargetY(float y)
{
	if (this->y != y)
	{
		this->targetY = y;
		tickCounter = ticksToAdjust;
		adjustAmount = (y - this->y) / ticksToAdjust;
	}
}

EntityType Entity::getType()
{
	return type;
}

float Entity::getRotation()
{
	return rotation;
}

void Entity::setRotation(float rotation)
{
	this->rotation = rotation;
}

bool Entity::getVulnerable()
{
	return vulnerable;
}

int Entity::getHealth()
{
	return health;
}

void Entity::takeDamage(int amount)
{
	health -= amount;

	if (health <= 0)
		health = 0;
}

void Entity::setTargetRotation(float rotation)
{
	if (this->rotation != rotation)
	{
		this->targetRotation = rotation;
		tickCounter = ticksToAdjust;
		adjustAmount = (rotation - this->rotation) / ticksToAdjust;
	}
}

bool Entity::getNeedsAnimated()
{
	return needsAnimated;
}

void Entity::setNeedAnimated(bool needsAnimated)
{
	this->needsAnimated = needsAnimated;
}

void Entity::tick()
{
	if (tickCounter == 0)
	{
		tickCounter = -1;
		x = targetX;
		y = targetY;
		rotation = (int)targetRotation % 360;
		targetRotation = rotation;
	}

	if (x != targetX)
	{
		x += adjustAmount;
		tickCounter--;
	}

	if (y != targetY)
	{
		y += adjustAmount;
		tickCounter--;
	}

	if (rotation != targetRotation)
	{
		rotation += adjustAmount;
		tickCounter--;
	}

}

void Entity::addCollision(Entity* entity)
{
	if (find(collisions.begin(), collisions.end(), entity) == collisions.end())
		collisions.push_back(entity);
}

bool Entity::handleCollisions()
{
	collisions.clear();
	return false;
}

void Entity::animationDone()
{

}