#include <iostream>
#include "simplebot.h"

using namespace std;

SimpleBot::SimpleBot()
{

}

void SimpleBot::takeTurn()
{
	switch (movementStage) {
		case Move:
			if (amOnExit()) return;
			if (frontIsClear()) {
				move();
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
			
			if (pivoting) {
				pivoting = 0;
				lastTurn = lastTurn == Left ? Right : Left;
			}

			movementStage = Move;
			break;

		default:
			movementStage = Move;
			break;
	}
	
}




