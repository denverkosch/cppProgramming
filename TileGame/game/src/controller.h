#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <string>
#include "world.h"
#include "pubsub.h"
#include "entity.h"
#include "entityView.h"

class Controller : public Subscriber {
    private:
        World world;
        vector<EntityView *> views;
    public:
        void gameLoop();
        void receiveMessage(string channel, string message, void* data);
};

#endif