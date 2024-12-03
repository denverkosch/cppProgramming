#include <iostream>
#include <vector>
#include "raylib.h"
#include "world.h"
#include "pubsub.h"
#include "entity_view.h"
#include "botdata.h"

// INCLUDING YOUR OWN BOTS Step 1: include your bot's header file
#include "simplebot.h"
#include "targetbot.h"
#include "denverbot.h"

class Controller : public Subscriber
{
private:
    World world;
    vector<EntityView*> views;

public:
    void gameLoop();
    void receiveMessage(string channel, string message, void* data);
};

int main(void)
{
    Controller controller;
    controller.gameLoop();

    return 0;
}

void Controller::gameLoop()
{
    const int screenWidth = 768;
    const int screenHeight = 576;
    int ticksThisTurn = 0;

    PubSub::subscribe("entity", this);

    InitWindow(screenWidth, screenHeight, "BBots Exercise 1");
    SetTargetFPS(60);

    // INCLUDING YOUR OWN BOTS Step 2: change the number of bots to up to 4
    vector<BotData*> botentities = world.initWorld(screenWidth, screenHeight, 2);
    vector<BattleBot*> bots;

    BattleBot* bot1;

    // INCLUDING YOUR OWN BOTS Step 3: To include your own bots replace SimpleBot() with your 
    // bot's constructor call.  
    // 
    // To have more than one bot in the arena, copy the next three lines and change them
    // for each extra bot.  Don't forget to change the botentities index for each successive bot!
    //
    // Colors cycle based on bot order: Blue, Green, Red, Tan
    bot1 = new SimpleBot();
    bot1->data = botentities[0];
    bots.push_back(bot1);

    bot1 = new DenverBot();
    bot1->data = botentities[1];
    bots.push_back(bot1);
  

    // Terrain assets pulled from: 
    // https://kenney-assets.itch.io/top-down-tanks-redux
    // https://kenney-assets.itch.io/pirate-pack

    int turnsOnExit = 0;
 
    while (!WindowShouldClose())
    {
        // Give the world a chance to progress
        world.tick();

        ticksThisTurn++;

        if (ticksThisTurn == ticksPerTurn)
        {
            ticksThisTurn = 0;

            for (BattleBot* bot : bots)
                if (bot->getHealth() > 0)
                    bot->takeTurn();
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw the views
        for (EntityView* view : views)
            view->draw();

        EndDrawing();
    }

    CloseWindow();
}

void Controller::receiveMessage(string channel, string message, void* data)
{
    // On the "entity" channel there can be "new" and "delete" messages.

    if (channel == "entity" && message == "new")
    {
        // Create a view for the entity
        EntityView* view = new EntityView((Entity*)data);
        views.push_back(view);
    }

    if (channel == "entity" && message == "delete")
    {
        // Try to find the view for the entity that's being deleted
        for (int i = 0; i < views.size(); i++)
        {
            if (views[i]->isViewFor((Entity*)data))
            {
                // Delete this view's memory
                delete views[i];
                // Delete it from the vector
                views.erase(views.begin() + i);
                // and stop looking, since we found the right view
                break;
            }
        }
    }
}
