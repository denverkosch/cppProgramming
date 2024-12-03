#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include "battlebot.h"

class SimpleBot: public BattleBot
{
private:
	int state = 0;

public:
	SimpleBot();

	void takeTurn();
};

#endif
