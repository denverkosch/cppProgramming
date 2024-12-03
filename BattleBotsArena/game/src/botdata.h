#ifndef BOTDATA_H
#define BOTDATA_H

#include "entity.h"
#include "entitydata.h"
#include "shotentity.h"

// We cannot include world.h because it includes this header file
// so at least tell C++ that the World class exists to make the
// compiler happy.
class World;

class BotData: private Entity
{
private:
	bool doingAction = false;
	World* world;

	ShotEntity* shot = NULL;

	void tick();

public:
	BotData(float x, float y, int width, int height, EntityType type, float rotation, World *world);

	void turnLeft();
	void turnRight();
	bool frontIsClear();
	bool rightIsClear();
	bool leftIsClear();
	bool facingNorth();
	bool facingSouth();
	bool facingEast();
	bool facingWest();
	bool amOnExit();
	EntityData scan();
	void move();
	void fire();
	bool canFire();
	int getHealth();
	void setTag(char *t);
	int getRow();
	int getCol();
};

#endif