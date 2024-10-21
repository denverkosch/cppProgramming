#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include "entity.h"
#include "pubsub.h"

class PlayerEntity : public Entity {
    private:
        int health;
        float targetX;
        float targetY;
        float speedX;
        float speedY;
        int movementCountdown;
    public:
        PlayerEntity(float x, float y, int width, int height, EntitySpecific skin);
        ~PlayerEntity();
        void tick();
        EntitySpecific getSkin();
        void setSkin(EntitySpecific skin);
        void receiveMessage(string channel, string message, void* data);
        void setHealth(int health);
        int getHealth();

};

#endif