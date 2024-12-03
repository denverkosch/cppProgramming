#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "entity.h"
#include "textures.h"
#include "raylib.h"
#include <map>


struct ActionInfo {
    int row;
    int actionFrames;
};

struct SpriteInfo {
    string fileName;
    int numFrames;
    int numActions;
    map<Action, ActionInfo> actions;
};

class EntityView {
    private:
        Entity* entity;
        Texture2D texture;
        int frame;
        int delay;
        SpriteInfo spriteInfo;

    public:
        EntityView(Entity* entity);
        ~EntityView();
        void draw(int vx, int vy, int vdx, int vdy, int vw, int vh);
        bool isViewFor(Entity* entity);
};

#endif 