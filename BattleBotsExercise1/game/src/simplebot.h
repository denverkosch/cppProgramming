#ifndef SIMPLEBOT_H
#define SIMPLEBOT_H

#include "battlebot.h"
#include <vector>

using namespace std;

enum MovementStage {
	Move,
	FirstTurn,
	MoveInTurn,
	SecondTurn
};

enum Turn {
	Left,
	Right
};

class SimpleBot: public BattleBot
{
private:
	Turn lastTurn = Left;
	int pivoting = 0;
	MovementStage movementStage = Move;

public:
	SimpleBot();

	void takeTurn();
};

#endif
