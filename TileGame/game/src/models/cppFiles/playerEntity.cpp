#include "playerEntity.h"
#include "raylib.h"
#include "pubsub.h"
#include <iostream>

using namespace std;

PlayerEntity::PlayerEntity(float x, float y, int width, int height, EntitySpecific skin) : Entity(x, y, width, height, PLAYER, skin) {
    PubSub::subscribe("action", this);
    movementCountdown = 0;
	targetX = 0;
	targetY = 0;
	speedX = 0;
	speedY = 0;
    health = 100;
}

PlayerEntity::~PlayerEntity() {
	PubSub::unsubscribe("action", this);
}


void PlayerEntity::tick() {
	if (movementCountdown > 0) {
		movementCountdown--;
		if (movementCountdown == 0) {
			setMoving(false);
			setX(targetX);
		} else setX(getX() + speedX);
	}

	speedY += 0.5;

	if (speedY > 10) speedY = 10;

	if (getY() + speedY > 872) {
		setY(872);
		speedY = 0;
		setFalling(false);
	} else setY(getY() + speedY);

	Vector2 position = { getX(), getY() };
	// PubSub::publish("player", "location", &position);
}

void PlayerEntity::receiveMessage(string channel, string message, void* data) {
	if (channel == "action" && message == "player") {
		Action* action = (Action*)data;

		if (*action == MV_LEFT && *action == MV_RIGHT) {
			setMoving(false);
		}

		if (*action == MV_LEFT) {
			targetX = getX() - 10;
			targetY = getY();
			// speedY = 0;
			speedX = - 200.0 / 60.0;
			setMoving(true);
			setFacing(LEFT);
			movementCountdown = 5;
		}

		if (*action == MV_RIGHT) {
			targetX = getX() + 10;
			targetY = getY();
			// speedY = 0;
			speedX = 200.0 / 60.0;
			setMoving(true);
			setFacing(RIGHT);
			movementCountdown = 5;
		}

		if (*action == JUMP) {
			cout << isFalling() << endl;
			if (!isFalling()) {
				speedY = -11;
				setFalling(true);
			}
		}

		if (*action == IDLE) setMoving(false);
	}
}

void PlayerEntity::setHealth(int health) {
    this->health = health;
}

int PlayerEntity::getHealth() {
    return health;
}

EntitySpecific PlayerEntity::getSkin() {
    return specific;
}

void PlayerEntity::setSkin(EntitySpecific skin) {
    specific = skin;
}