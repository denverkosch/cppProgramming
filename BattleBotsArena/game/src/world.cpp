#include <iostream>
#include <cstdlib>
#include <ctime>
#include "entitydata.h"
#include "world.h"
#include "pubsub.h"
#include "utility.h"
#include "shotentity.h"

World::World()
{
	unsigned int seed = time(NULL);
	srand(seed);

	cout << "World seed: " << seed << endl;

	PubSub::subscribe("action", this);
}

void World::receiveMessage(string channel, string message, void* data)
{
}

void World::tick()
{
	for (Entity *entity : entities)
		entity->tick();
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

vector<BotData *> World::initWorld(int width, int height, int numBots)
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

	// Randomly place some interior obstacles
	int numObstacles = (rand() % 8) + 1;
	int rows = height / tileSize - 2;
	int cols = width / tileSize - 2;
	int row;
	int col;

	EntityType types[] = { Tower, Tree, Rock1, Rock2};

	for (int i = 0; i < numObstacles; i++)
	{
		EntityType type = types[rand() % 4];
		row = rand() % rows;
		col = rand() % cols;

		while (!isClear(col * tileSize + tileSize, row * tileSize + tileSize))
		{
			row = rand() % rows;
			col = rand() % cols;
		}

		wall = new Entity(col * tileSize + tileSize, row * tileSize + tileSize, tileSize, tileSize, type);
		PubSub::publish("entity", "new", wall);
		entities.push_back(wall);
	}

	EntityType tankTypes[] = {TankA, TankB, TankC, TankD};

	for (int i = 0; i < numBots; i++)
	{
		// Place the battle bot at a random position, but not on an obstacle
		row = rand() % rows;
		col = rand() % cols;

		while (!isClear(col * tileSize + tileSize, row * tileSize + tileSize))
		{
			row = rand() % rows;
			col = rand() % cols;
		}

		BotData* bot = new BotData(col * tileSize + tileSize, row * tileSize + tileSize, tileSize, tileSize, tankTypes[i], 0, this);
		result.push_back(bot);
		PubSub::publish("entity", "new", bot);
		entities.push_back((Entity*)bot);
	}

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

EntityData World::scan(int x, int y, int rotation)
{
	Vector2 forward = getForwardCoords(x, y, rotation, tileSize);

	while (true)
	{
		for (Entity* entity : entities)
		{
			if (entity->getX() == forward.x && entity->getY() == forward.y)
				return EntityData(entity);
		}

		// Didn't find anything, keep going
		forward = getForwardCoords(forward.x, forward.y, rotation, tileSize);
	}
}

void World::addEntity(Entity* entity)
{
	PubSub::publish("entity", "new", entity);
	entities.push_back(entity);
}

void World::removeEntity(Entity* entity)
{
	vector<Entity*>::iterator result = find(entities.begin(), entities.end(), entity);
	if (result != entities.end())
	{
		entities.erase(result);
		PubSub::publish("entity", "delete", entity);
		delete entity;
	}
}

bool World::entityExists(Entity* entity)
{
	vector<Entity*>::iterator result = find(entities.begin(), entities.end(), entity);
	return result != entities.end();
}

vector<EntityData> World::inSameTile(int x, int y)
{
	vector<EntityData> results;

	for (Entity* entity : entities)
	{
		if (entity->getX() == x && entity->getY() == y)
			results.push_back(EntityData(entity));
	}

	return results;
}

void World::shotHits(ShotEntity *shot, int damage, Entity* source)
{
	int tileX = (((int)shot->getX()) / tileSize) * tileSize;
	int tileY = (((int)shot->getY()) / tileSize) * tileSize;

	vector<Entity*> toRemove;
	vector<Entity> tilesToCheck;

	// Precalculate the adjoining 8 tile coordinates
	// The entity type here doesn't matter, just the 
	// coordinates and width and height
	// 
	// West
	Entity west(tileX - tileSize, tileY, tileSize, tileSize, EntityType::Exit);
	tilesToCheck.push_back(west);

	// East
	Entity east(tileX + tileSize, tileY, tileSize, tileSize, EntityType::Exit);
	tilesToCheck.push_back(east);

	// North
	Entity north(tileX, tileY - tileSize, tileSize, tileSize, EntityType::Exit);
	tilesToCheck.push_back(north);

	// South
	Entity south(tileX, tileY + tileSize, tileSize, tileSize, EntityType::Exit);
	tilesToCheck.push_back(south);

	// Northwest
	Entity northwest(tileX - tileSize, tileY - tileSize, tileSize, tileSize, EntityType::Exit);
	tilesToCheck.push_back(northwest);

	// Northeast
	Entity northeast(tileX + tileSize, tileY - tileSize, tileSize, tileSize, EntityType::Exit);
	tilesToCheck.push_back(northeast);

	// Southwest
	Entity southwest(tileX - tileSize, tileY + tileSize, tileSize, tileSize, EntityType::Exit);
	tilesToCheck.push_back(southwest);

	// Southeast
	Entity southeast(tileX + tileSize, tileY + tileSize, tileSize, tileSize, EntityType::Exit);
	tilesToCheck.push_back(southeast);

	for (Entity* entity : entities)
	{
		// A direct shot does full damage
		if (entity != source && doesShotHit(shot, entity))
			processShotHit(damage, entity, toRemove);
		else
		{
			// Entities on adjoining tiles take half damage
			for (Entity tile : tilesToCheck)
				if (doesShotHit(&tile, entity))
					processShotHit(damage / 2, entity, toRemove);
		}
	}

	// Don't modify the entities list while we're looping through it,
	// instead remember every entity that needs destroyed and process
	// those outside of the entities loop.
	for (Entity* entity : toRemove)
	{
		removeEntity(entity);
	}
}

void World::processShotHit(int damage, Entity* entity, vector<Entity*> &toRemove)
{
	if (entity->getVulnerable())
	{
		entity->takeDamage(damage);

		if (entity->getHealth() == 0)
			toRemove.push_back(entity);
	}
}

bool World::doesShotHit(Entity *shot, Entity *entity)
{
	Rectangle entityRec = { entity->getX(), entity->getY(), (float)entity->getWidth(), (float)entity->getHeight() };
	Rectangle shotRec = { shot->getX(), shot->getY(), (float)shot->getWidth(), (float)shot->getHeight() };

	return CheckCollisionRecs(entityRec, shotRec);
}