#include <iostream>
#include <map>
#include <string>
#include "entity_view.h"
#include "textures.h"

const int animationDelay = 2;

struct SpriteSheetInfo
{
	string fileName;
	int numFrames = 0;
};

map<EntityType, SpriteSheetInfo> spriteMapping = {
	{TankA, {"resources/tankA.png", 1}},
	{TankB, {"resources/tankB.png", 1}},
	{TankC, {"resources/tankC.png", 1}},
	{TankD, {"resources/tankD.png", 1}},
	{Tree, {"resources/tree.png", 1}},
	{WallNS, {"resources/wallns.png", 1}},
	{WallEW, {"resources/wallew.png", 1}},
	{WallN, {"resources/walln.png", 1}},
	{WallS, {"resources/walls.png", 1}},
	{WallE, {"resources/walle.png", 1}},
	{WallW, {"resources/wallw.png", 1}},
	{CornerEN, {"resources/corneren.png", 1}},
	{CornerES, {"resources/corneres.png", 1}},
	{CornerWN, {"resources/cornerwn.png", 1}},
	{CornerWS, {"resources/cornerws.png", 1}},
	{Tower, {"resources/tower.png", 1}},
	{Rock1, {"resources/rock1.png", 1}},
	{Rock2, {"resources/rock2.png", 1}},
	{Exit, {"resources/exit.png", 1}},
	{TankShot, {"resources/shotRed.png", 1}},
	{Explosion, {"resources/explosion.png", 5}},
};

EntityView::EntityView(Entity *entity)
{
	this->entity = entity;
	texture = Textures::loadTexture(spriteMapping[entity->getType()].fileName);
	frame = 0;
	delay = animationDelay;
}

bool EntityView::isViewFor(Entity* entity)
{
	return this->entity == entity;
}

void EntityView::draw()
{
	int numFrames = spriteMapping[entity->getType()].numFrames;
	float frameWidth = texture.width / numFrames;
	float frameHeight = entity->getHeight();
	int row = 0; 
	Rectangle frameRec = { frame * frameWidth, row * frameHeight, frameWidth, frameHeight };

	float x = entity->getX();
	float y = entity->getY();

	// With DrawTexturePro, the origin is in sprite coords and the x,y of where it
	// gets drawn is where the origin is drawn.
	DrawTexturePro(texture, frameRec, { x + frameWidth / 2, y + frameHeight / 2, frameWidth, frameHeight }, { frameWidth / 2, frameHeight / 2 }, entity->getRotation(), WHITE);

	if (entity->getVulnerable())
	{
		int fontSize = 24;
		string healthString = to_string(entity->getHealth());
		char *tag = entity->getTag();
		int stringWidth = MeasureText(healthString.c_str(), fontSize);
		int tagWidth = MeasureText(tag, fontSize);

		DrawText(healthString.c_str(), x + frameWidth/2 - stringWidth/2, y + frameWidth/2 - GetFontDefault().baseSize + 10, fontSize, MAGENTA);
		DrawText(tag, x + frameWidth / 2 - tagWidth / 2, y + frameWidth / 2 - GetFontDefault().baseSize - 10, fontSize, MAGENTA);
		//DrawRectangle(x + 2, y + frameWidth / 2, (frameWidth - 2) * entity->getHealth() / 100, 4, MAGENTA);
	}

	// Now that we've drawn the current frame, see if the entity needs animated
	if (entity->getNeedsAnimated())
	{
		delay--;

		if (delay == 0)
		{
			frame = (frame + 1) % numFrames;
			delay = animationDelay;

			if (frame == 0)
				entity->animationDone();
		}
	}
}