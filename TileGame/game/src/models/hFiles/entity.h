#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "pubsub.h"

using namespace std;


enum EntityType {
    PLAYER,
    ENEMY,
    TERRAIN
};

enum EntitySpecific {
    FIGHTER,
    SHINOBI,
    SAMURAI,
    SKELE,
    FLOOR,
    PLATFORM,
    WALL
};

enum EntityFacing {
    LEFT,
    RIGHT
};

enum Action {
    IDLE,
    MV_LEFT,
    MV_RIGHT,
    JUMP,
    ATTACK1,
    ATTACK2,
    ATTACK3,
    BLOCK,
    DIE
};

class Entity : public Subscriber {
    private:
        float x;
        float y;
        int width;
        int height;
        EntityType type;
        EntityFacing facing;
        bool moving;
        bool falling;
        Action action;

    protected:
        vector<Entity*> collisions;
        EntitySpecific specific;
    public:
        Entity(float x, float y, int width, int height, EntityType type, EntitySpecific specific, EntityFacing facing = RIGHT);
        virtual ~Entity();
        float getX();
        float getY();
        int getWidth();
        int getHeight();
        EntityType getType();
        EntitySpecific getSpecific();
        EntityFacing getFacing();
        bool isMoving();
        bool isFalling();
        Action getAction();

        void setX(float x);
        void setY(float y);
        void setFacing(EntityFacing facing);
        void setMoving(bool moving);
        void setFalling(bool falling);
        void setAction(Action action);

        virtual void tick();

        void addCollision(Entity* entity);
        virtual bool handleCollisions();
};


#endif