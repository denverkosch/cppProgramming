#ifndef DENVERBOT_H
#define DENVERBOT_H

#include "battlebot.h"
#include <stdbool.h>


enum Stage {
	Scan,
	Move,
	FirstTurn,
	MoveInTurn,
	SecondTurn,
};

enum Turn {
	Left,
	Right
};

class DenverBot: public BattleBot {
private:
	enum Turn lastTurn = Left;
	int scanProgress = 0;
	bool pivoting = false;
	Stage movementStage = Scan;
	bool enemyFound = false;
	int distToEnemy = 0;
	float enemyRotation = 0;
	bool tracking = false;


public:
	DenverBot();
	int isWall(EntityType current);
	void takeTurn();
	bool enemyAhead();
	int findDistance(EntityData data);
	void hunt(EntityData data);
	void pursue();
};

#endif
