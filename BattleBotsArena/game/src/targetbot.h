#ifndef TARGETBOT_H
#define TARGETBOT_H

#include "battlebot.h"

class TargetBot: public BattleBot
{
private:
	int state = 0;

public:
	TargetBot();

	void takeTurn();
};

#endif
