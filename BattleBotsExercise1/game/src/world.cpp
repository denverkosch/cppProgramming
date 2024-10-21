#include <iostream>
#include <cstdlib>
#include <ctime>
#include "world.h"
#include "pubsub.h"
#include "raylib.h"

World::World()
{
	srand(time(NULL));

	PubSub::subscribe("action", this);
}

void World::receiveMessage(string channel, string message, void* data)
{
}

void World::tick()
{
	for (Entity *entity : entities)
		entity->tick();

	// Detect collisions
	collisions.clear();
	for (Entity* entity : entities)
	{
		if (entity->getMoving() || entity->getFalling())
		{
			for (Entity* entity2 : entities)
			{
				if (entity != entity2)
				{
					checkCollision(entity, entity2);
				}
			}
		}
	}

	// Handle collisions
	deletions.clear();
	for (Entity* entity : collisions)
	{
		if (entity->handleCollisions())
			deletions.push_back(entity);
	}

	// Remove deleted entities
	for (Entity* entity : deletions)
	{
		// Remove from the entities array
		vector<Entity*>::iterator result = find(entities.begin(), entities.end(), entity);
		if (result != entities.end())
			entities.erase(result);

		// Tell the views about the deletion
		PubSub::publish("entity", "delete", entity);

		// Delete memory
		delete entity;
	}
}

void World::checkCollision(Entity* entity, Entity* entity2)
{
	Rectangle rec1 = { entity->getX(), entity->getY(), (float)entity->getWidth(), (float)entity->getHeight() };
	Rectangle rec2 = { entity2->getX(), entity2->getY(), (float)entity2->getWidth(), (float)entity2->getHeight() };

	if (CheckCollisionRecs(rec1, rec2))
	{
		entity->addCollision(entity2);
		if (find(collisions.begin(), collisions.end(), entity) == collisions.end())
			collisions.push_back(entity);

		if (!entity2->getMoving())
		{
			entity2->addCollision(entity);
			if (find(collisions.begin(), collisions.end(), entity2) == collisions.end())
				collisions.push_back(entity2);
		}
	}
}

void World::clearWorld()
{
	for (Entity* entity : entities)
	{
		// Let everyone know we're deleting this entity
		PubSub::publish("entity", "delete", entity);
		delete entity;
	}

	entities.clear();
}

vector<BotData *> World::initWorld(int width, int height)
{
	vector<BotData *> result;

	for (int x = tileSize; x < width/tileSize*tileSize - tileSize; x += tileSize)
	{
		Entity* wall = new Entity(x, 0, tileSize, tileSize, WallEW);
		PubSub::publish("entity", "new", wall);
		entities.push_back(wall);

		wall = new Entity(x, height/tileSize*tileSize - tileSize, tileSize, tileSize, WallEW);
		PubSub::publish("entity", "new", wall);
		entities.push_back(wall);
	}

	for (int y = tileSize; y < height/tileSize*tileSize - tileSize; y += tileSize)
	{
		Entity* wall = new Entity(0, y, tileSize, tileSize, WallNS);
		PubSub::publish("entity", "new", wall);
		entities.push_back(wall);

		wall = new Entity(width/tileSize*tileSize - tileSize, y, tileSize, tileSize, WallNS);
		PubSub::publish("entity", "new", wall);
		entities.push_back(wall);
	}

	Entity* wall = new Entity(0, 0, tileSize, tileSize, CornerES);
	PubSub::publish("entity", "new", wall);
	entities.push_back(wall);

	wall = new Entity(0, height/tileSize*tileSize - tileSize, tileSize, tileSize, CornerEN);
	PubSub::publish("entity", "new", wall);
	entities.push_back(wall);

	wall = new Entity(width/tileSize*tileSize-tileSize, 0, tileSize, tileSize, CornerWS);
	PubSub::publish("entity", "new", wall);
	entities.push_back(wall);

	wall = new Entity(width/tileSize*tileSize - tileSize, height/tileSize*tileSize - tileSize, tileSize, tileSize, CornerWN);
	PubSub::publish("entity", "new", wall);
	entities.push_back(wall);

	// Randomly place an exit entity somewhere in the interior
	int rows = height / tileSize - 2;
	int cols = width / tileSize - 2;
	int row = rand() % rows;
	int col = rand() % cols;

	wall = new Entity(col * tileSize + tileSize, row * tileSize + tileSize, tileSize, tileSize, Exit);
	PubSub::publish("entity", "new", wall);
	entities.push_back(wall);

	// Place the battle bot at a random position
	row = rand() % rows;
	col = rand() % cols;

	BotData* bot = new BotData(col * tileSize + tileSize, row * tileSize + tileSize, tileSize, tileSize, TankA, 0, this);
	result.push_back(bot);
	PubSub::publish("entity", "new", bot);
	entities.push_back((Entity *) bot);

	return result;
}

bool World::isClear(int x, int y)
{
	for (Entity* entity : entities)
	{
		if (entity->getX() == x && entity->getY() == y && entity->getType() != Exit)
			return false;
	}

	return true;
}

bool World::isOnExit(int x, int y)
{
	for (Entity* entity : entities)
	{
		if (entity->getX() == x && entity->getY() == y && entity->getType() == Exit)
			return true;
	}

	return false;
}
