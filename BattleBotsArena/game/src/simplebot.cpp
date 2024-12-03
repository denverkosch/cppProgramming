#include <iostream>
#include "simplebot.h"

SimpleBot::SimpleBot()
{

}

void SimpleBot::takeTurn()
{
	setTag("SimpleBot");

	if (state == 0 && canFire())
	{
		fire();
		state++;
	}
	else if (state == 1)
	{
		turnLeft();
		state = 0;
	}
}
