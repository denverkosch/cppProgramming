#ifndef BATTLEBOT_H
#define BATTLEBOT_H

#include "botdata.h"

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
	void move();

	virtual void takeTurn() = 0;
};

#endif
