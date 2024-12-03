#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

using namespace std;

const int ticksPerTurn = 15;
const int tileSize = 64;

enum EntityType { TankA, TankB, TankC, TankD, WallNS, WallEW, WallN, WallS, WallE, WallW, Tower, CornerEN, CornerES, CornerWN, CornerWS, Tree, Rock1, Rock2, Exit, TankShot, Explosion };

class Entity
{
private:
	float x;
	float y;
	float rotation;
	float targetX;
	float targetY;
	float targetRotation;

	int width;
	int height;
	EntityType type;
	bool needsAnimated;
	bool vulnerable;
	int health = 100;
	char *tag;

	int tickCounter;
	float adjustAmount;

protected:
	vector<Entity*> collisions;

public:
	Entity(float x, float y, int width, int height, EntityType type, float rotation = 0, bool vulnerable = false);

	float getX();
	float getY();
	int getWidth();
	int getHeight();
	EntityType getType();
	float getRotation();
	bool getNeedsAnimated();
	bool getVulnerable();
	int getHealth();
	void takeDamage(int amount);
	char *getTag();

	void setX(float x);
	void setY(float y);
	void setRotation(float rotation);
	void setTargetX(float x);
	void setTargetY(float y);
	void setTargetRotation(float rotation);
	void setNeedAnimated(bool moving);
	void setTag(char *tag);

	void addCollision(Entity* entity);
	virtual bool handleCollisions();
	virtual void animationDone();

	virtual void tick();
};

#endif