#ifndef BATTLEBOT_H
#define BATTLEBOT_H

#include "botdata.h"
#include "entitydata.h"

class BattleBot
{
private:

public:
	BotData *data;
	BattleBot();

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

	virtual void takeTurn() = 0;
};

#endif