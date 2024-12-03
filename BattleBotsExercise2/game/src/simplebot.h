#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include "battlebot.h"

enum Stage {
	Scan,
	Move,
	FirstTurn,
	MoveInTurn,
	SecondTurn,
	ExitFound
};

enum Turn {
	Left,
	Right
};

class SimpleBot: public BattleBot {
private:
	enum Turn lastTurn = Left;
	int scanProgress = 0;
	int pivoting = 0;
	Stage movementStage = Scan;

public:
	SimpleBot();
	int isWall(EntityType current);
	void takeTurn();
};



#endif
