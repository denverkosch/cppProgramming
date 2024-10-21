#include "raylib.h"
#include <math.h>
#include "controller.h"
#include "world.h"
#include "entity.h"
#include "entityView.h"
#include "playerEntity.h"


int viewportWidth = 1440;
int viewportHeight = 750;
int viewportX = 160;
int viewportY = 280;
int viewportDrawX = 0;
int viewportDrawY = 0;

void Controller::receiveMessage(string channel, string message, void* data) {
    // On the "entity" channel there can be "new" and "delete" messages.
    if (channel == "entity" && message == "new") {
        // Create a view for the entity
        EntityView* view = new EntityView((Entity *) data);
        views.push_back(view);
    }

    if (channel == "entity" && message == "delete") {
        // Try to find the view for the entity that's being deleted
        for (int i = 0; i < views.size(); i++) {
            if (views[i]->isViewFor((Entity*) data)) {
                delete views[i];
                views.erase(views.begin() + i);
                break;
            }
        }
    }

    if (channel == "player" && message == "location") {
        Vector2* position = (Vector2*)data;
        viewportX = position->x - viewportWidth / 2;
    }
}

void Controller::gameLoop() {

    InitWindow(viewportWidth, viewportHeight, "Tile Game");

    map<KeyboardKey, Action> keyMapping;

    if (IsKeyPressed(KEY_A)) world.getPlayer()->setFacing(LEFT);
    else if (IsKeyPressed(KEY_D)) world.getPlayer()->setFacing(RIGHT);

    keyMapping[KEY_W] = JUMP;
    keyMapping[KEY_A] = MV_LEFT;
    keyMapping[KEY_D] = MV_RIGHT;
    keyMapping[KEY_J] = ATTACK1;
    keyMapping[KEY_K] = ATTACK2;
    keyMapping[KEY_L] = ATTACK3;
    keyMapping[KEY_SPACE] = BLOCK;


    PubSub::subscribe("entity", this);
    PubSub::subscribe("player", this);

    float x = 320;
    float y = 740;
    PlayerEntity* player = new PlayerEntity(x, y, 128, 128, FIGHTER);
    world.addPlayer(player);

    PubSub::publish("entity", "new", player);

    SetTargetFPS(60);

    
    while (!WindowShouldClose()) {

        // Handle user input
        for (auto &i : keyMapping) {
            if (IsKeyPressed(i.first))
            {
                Action action = i.second;
                PubSub::publish("action", "player", &action);
            }
        }

        // Give the world a chance to progress
        world.tick();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the views
        for (EntityView *view : views)
            view->draw(viewportX, viewportY, viewportDrawX, viewportDrawY, viewportWidth, viewportHeight);


        EndDrawing();
    }

    CloseWindow();
}

int main(void) {
    Controller controller;
    controller.gameLoop();
    return 0;
}