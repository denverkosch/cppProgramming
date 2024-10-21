#include "entity.h"
#include "pubsub.h"
#include "world.h"
#include "playerEntity.h"


World::World() {
	player = NULL;
	srand(time(NULL));
	PubSub::subscribe("action", this);
}

void World::clearWorld() {
    for (int i = 0; i < entities.size(); i++) delete entities[i];
    entities.clear();
}

void World::addEntity(Entity* entity) {
    PubSub::publish("entity", "new", entity);
    entities.push_back(entity);
}

void World::addPlayer(Entity* entity) {
    addEntity(entity);
    player = entity;
}

Entity* World::getPlayer() {
    return player;
}

void World::tick() {
	for (Entity *entity : entities) entity->tick();

	// Detect collisions
	collisions.clear();
	for (Entity* entity : entities) {
		if (entity->isMoving() || entity->isFalling()) {
			for (Entity* entity2 : entities) {
				if (entity != entity2) checkCollision(entity, entity2);
			}
		}
	}

	// Handle collisions
	deletions.clear();
	for (Entity* entity : collisions) {
		if (entity->handleCollisions()) deletions.push_back(entity);
	}

	// Remove deleted entities
	for (Entity* entity : deletions) {
		vector<Entity*>::iterator result = find(entities.begin(), entities.end(), entity);

		if (result != entities.end())
			entities.erase(result);

		PubSub::publish("entity", "delete", entity);
		delete entity;
	}
}

vector<Entity*> World::getEntities() {
    return entities;
}

void World::checkCollision(Entity* entity1, Entity* entity2) {
    if (entity1->getX() < entity2->getX() + entity2->getWidth() &&
        entity1->getX() + entity1->getWidth() > entity2->getX() &&
        entity1->getY() < entity2->getY() + entity2->getHeight() &&
        entity1->getY() + entity1->getHeight() > entity2->getY()) {
            entity1->addCollision(entity2);
            entity2->addCollision(entity1);
        }
}

void World::receiveMessage(string channel, string message, void* data) {
	if (channel == "action" && message == "player") {
		PlayerActionMessage* pam = (PlayerActionMessage*)data;
		player->setAction(pam->action);
	}
}