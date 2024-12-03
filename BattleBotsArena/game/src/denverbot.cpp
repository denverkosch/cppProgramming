#include <iostream>
#include <cstdlib>
#include "simplebot.h"
#include "denverbot.h"
#include "entitydata.h"
#include <stdbool.h>


DenverBot::DenverBot() {
	srand(time(0));
}

void DenverBot::takeTurn() {
	setTag("DenverBot");

    EntityData data = scan();
    EntityType type = data.getType();

	if (type == TankShot) {
		int rowDiff = abs(data.getRow() - getRow());
		int colDiff = abs(data.getCol() - getCol());
		if (rowDiff > 2 || colDiff > 2) movementStage = FirstTurn;
	}

	enemyFound = (type == TankA || type == TankB || type == TankC || type == TankD) ? true : false;
	tracking = !enemyFound && distToEnemy > 0 ? true : false;

	if (!enemyFound && !tracking) {
		switch (movementStage) {
			case Scan:
				if (scanProgress == 0) {
					if (isWall(type)) {
						movementStage = FirstTurn;
						break;
					}
					turnLeft();
					scanProgress++;
				} 
				else if (scanProgress == 1) {
					turnRight();
					scanProgress++;
				} 
				else if (scanProgress == 2) {
					turnRight();
					scanProgress++;
				} 
				else if (scanProgress == 3) {
					turnLeft();
					scanProgress = 0;  // Reset for next scan cycle
					movementStage = Move;  // Only move after the scan cycle is done
				}
				break;
			case Move:
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
					pivoting = false;
				}
				else pivoting = true;
				
				movementStage = SecondTurn;
				break;

			case SecondTurn:
				if (lastTurn == Left) turnLeft();
				else turnRight();
				
				if (pivoting && isWall(scan().getType()))
					lastTurn = (lastTurn == Left) ? Right : Left;

				movementStage = Scan;
				break;
			default:
				movementStage = Scan;
				break;
		}
	}
	else if (enemyFound) {
		enemyRotation = data.getRotation();
		distToEnemy = findDistance(data);
		if (canFire() && (distToEnemy > 1 || getHealth() > 20)) fire();
		else move();
		if (distToEnemy == 1) turnLeft();
	}
	else if (tracking) {
		if (distToEnemy == 0) {
			if (enemyRotation == 0) turnRight();
			else turnLeft();

			enemyFound = enemyAhead();
			if (enemyFound) distToEnemy = findDistance(scan());
		}
		else if (distToEnemy == 2) {
			if (enemyRotation == 0) {
				if (rand() % 2 == 0) turnRight();
				else turnLeft();
			}
			else {
				if (rand() % 2 == 0) turnLeft();
				else turnRight();
			}
		}
		move();
		if (distToEnemy > 0) distToEnemy--;
		if (distToEnemy == 0) tracking = false;
	}
	else movementStage = Scan;
	
}

int DenverBot::isWall(EntityType currentType) {
	EntityType types[] = {WallNS, WallEW, WallN, WallS, WallE, WallW};
	for (int i = 0; i < sizeof(types); i++)
		if (currentType == types[i]) return 1;
	return 0;
}

bool DenverBot::enemyAhead() {
	EntityData data = scan();
	EntityType type = data.getType();
	return type == TankA || type == TankB || type == TankC || type == TankD ? true : false;
}

int DenverBot::findDistance(EntityData data) {
	int rowDiff = abs(data.getRow() - getRow());
	int colDiff = abs(data.getCol() - getCol());
	return rowDiff ? rowDiff : colDiff;
}
