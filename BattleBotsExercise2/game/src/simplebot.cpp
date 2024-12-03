#include <iostream>
#include "simplebot.h"

using namespace std;

SimpleBot::SimpleBot() {}

void SimpleBot::takeTurn()
{
	if (amOnExit()) return;


	switch (movementStage) {
		case Scan:
			if (scan().getType() == Exit) {
				movementStage = ExitFound;
				break;
			}
			if (scanProgress < 4) {
				turnRight();
				scanProgress++;
				break;
			}
			movementStage = Move;
			scanProgress = 0;
			break;

		case Move:
			if (amOnExit()) return;
			if (frontIsClear()) {
				move();
				movementStage = Scan;
				break;
			}
			movementStage = FirstTurn;
			break;

		case FirstTurn:
			if (lastTurn == Right) turnLeft();
			else turnRight();
			
			lastTurn = lastTurn == Left ? Right : Left;
			movementStage = MoveInTurn;
			break;

		case MoveInTurn:
			if (frontIsClear()) {
				move();
				pivoting = 0;
			}
			else pivoting = 1;
			
			movementStage = SecondTurn;
			break;

		case SecondTurn:
			if (lastTurn == Left) turnLeft();
			else turnRight();
			
			if (pivoting && isWall(scan().getType())) 
				lastTurn = (lastTurn == Left) ? Right : Left;

			movementStage = Scan;
			break;
		case ExitFound:
			if (!amOnExit()) move();
			break;
		default:
			movementStage = Scan;
			break;
	}
	
}

int SimpleBot::isWall(EntityType currentType) {
	EntityType types[] = {WallNS, WallEW, WallN, WallS, WallE, WallW};
	for (int i = 0; i < sizeof(types); i++)
		if (currentType == types[i]) return 1;
	return 0;
}