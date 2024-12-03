#include "utility.h"

Vector2 getForwardCoords(int x, int y, int rotation, int distance)
{
	if (rotation == 0)
		return { (float)x, (float)y - distance };

	if (rotation == 90)
		return { (float)x + distance, (float)y };

	if (rotation == 180)
		return { (float)x, (float)y + distance };

	if (rotation == 270)
		return { (float)x - distance, (float)y };

	return { (float)x, (float)y };
}
