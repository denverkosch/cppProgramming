#include "pubsub.h"
#include "entity.h"
#include "world.h"
#include "entity.h"


Entity::Entity(float x, float y, int width, int height, EntityType type, EntitySpecific specific, EntityFacing facing) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->type = type;
    this->facing = facing;
    this->specific = specific;
    moving = false;
    falling = false;
    action = IDLE;
}

Entity::~Entity() {
}

// ##################   Getters   ##################
float Entity::getX() {
    return x;
}

float Entity::getY() {
    return y;
}

int Entity::getWidth() {
    return width;
}

int Entity::getHeight() {
    return height;
}

EntityType Entity::getType() {
    return type;
}

EntitySpecific Entity::getSpecific() {
    return specific;
}

EntityFacing Entity::getFacing() {
    return facing;
}

bool Entity::isMoving() {
    return moving;
}

bool Entity::isFalling() {
    return falling;
}

Action Entity::getAction() {
    return action;
}

// ##################   Setters   ##################

void Entity::setX(float x) {
    this->x = x;
}

void Entity::setY(float y) {
    this->y = y;
}

void Entity::setFacing(EntityFacing facing) {
    this->facing = facing;
}

void Entity::setMoving(bool moving) {
    this->moving = moving;
}

void Entity::setFalling(bool falling) {
    this->falling = falling;
}

void Entity::setAction(Action action) {
    this->action = action;
}


// ##################   Other   ##################
void Entity::tick() {
    if (moving) x += (facing == RIGHT) ? 1: -1;
    if (falling) y += 1;
    if (!moving && !falling) action = IDLE;
}

void Entity::addCollision(Entity* entity) {
    collisions.push_back(entity);
}

bool Entity::handleCollisions() {
    for (Entity* entity : collisions) {
        if (entity->getType() == EntityType::PLAYER)
            PubSub::publish("entity", "entity_collision", this);
    }
    collisions.clear();
    return false;
}