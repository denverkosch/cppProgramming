#include <iostream>
#include "targetbot.h"

TargetBot::TargetBot()
{

}

void TargetBot::takeTurn()
{
	setTag("Target");

	if (state == 0)
	{
		turnLeft();
		state++;
	}
	else 
	{
		move();
	}
}
