#include "entity.h"
#include "world.h"
#include "pubsub.h"
#include "entityView.h"
#include "textures.h"
#include "raylib.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

map<EntitySpecific, SpriteInfo> spriteMapping = {
	{FIGHTER, {"resources/spritesheets/Fighter_Spritelist.png", 12, 10, {
            {IDLE, {0, 6}},
            {MV_LEFT, {2, 8}},
            {MV_RIGHT, {2, 8}},
            {JUMP, {3, 10}},
            {ATTACK1, {4, 4}},
            {ATTACK2, {5, 4}},
            {ATTACK3, {6, 4}},
            {BLOCK, {7, 2}},
            {DIE, {9, 3}}
        }
    }},
    {SHINOBI, {"resources/spritesheets/Shinobi_Spritelist.png", 12, 10, {
            {IDLE, {0, 6}},
            {MV_LEFT, {2, 8}},
            {MV_RIGHT, {2, 8}},
            {JUMP, {3, 12}},
            {ATTACK1, {4, 5}},
            {ATTACK2, {5, 3}},
            {ATTACK3, {6, 4}},
            {BLOCK, {7, 4}},
            {DIE, {9, 4}}
        }
    }},
	{SAMURAI, {"resources/spritesheets/Samurai_Spritelist.png", 12, 10, {
            {IDLE, {0, 6}},
            {MV_LEFT, {2, 8}},
            {MV_RIGHT, {2, 8}},
            {JUMP, {3, 12}},
            {ATTACK1, {4, 6}},
            {ATTACK2, {5, 4}},
            {ATTACK3, {6, 3}},
            {BLOCK, {7, 2}},
            {DIE, {9, 3}}
        }
    }},
    {SKELE, {"resources/spritesheets/Skeleton_Spritelist.png", 12, 10, {
            {IDLE, {0, 7}},
            {MV_LEFT, {1, 8}},
            {MV_RIGHT, {1, 8}},
            {JUMP, {3, 10}},
            {ATTACK1, {4, 7}},
            {ATTACK2, {5, 4}},
            {ATTACK3, {6, 7}},
            {DIE, {9, 3}}
        }
    }},
};



EntityView::EntityView(Entity* entity) {
    this->entity = entity;
    frame = 0;
    delay = 0;
    spriteInfo = spriteMapping[entity->getSpecific()];
    texture = Textures::loadTexture(spriteInfo.fileName);
}

EntityView::~EntityView() {
}

void EntityView::draw(int vx, int vy, int vdx, int vdy, int vw, int vh) {
    EntityFacing facing = entity->getFacing();

    int animationDelay = 20;
    ActionInfo action = spriteInfo.actions[entity->getAction()];
    int numFrames = spriteInfo.numFrames;
    int numActionFrames = action.actionFrames;

    if (entity->isMoving()) {
		delay--;

		if (delay == 0) {
			frame = (frame + 1) % numFrames;
			delay = animationDelay;
		}
	}
	else {
		frame = 0;
		delay = animationDelay;
	}

    float frameWidth = texture.width / numFrames;
	int row = action.row;
	Rectangle frameRec = { frame * frameWidth, row * frameWidth, frameWidth, frameWidth };

	float x = (entity->getX() - vx) + vdx;
	float y = (entity->getY() - vy) + vdy;

	DrawTextureRec(texture, frameRec, {x, y}, WHITE);

}

bool EntityView::isViewFor(Entity* entity) {
    return this->entity == entity;
}