#ifndef _SPRITELOADER_H_
#define _SPRITELOADER_H_

#include "../engine/SpriteManager.h"

#define MARIO_IDLE_RIGHT_ID "mario.idleRight"
#define MARIO_IDLE_LEFT_ID "mario.idleLeft"
#define MARIO_WALK_RIGHT_ID "mario.walkRight"
#define MARIO_WALK_LEFT_ID "mario.walkLeft"
#define MARIO_JUMP_RIGHT_ID "mario.jumpRight"
#define MARIO_JUMP_LEFT_ID "mario.jumpLeft"
#define MARIO_STOP_WALKING_RIGHT_ID "mario.stopWalkingRight"
#define MARIO_STOP_WALKING_LEFT_ID "mario.stopWalkingLeft"
#define MARIO_HOLD_FLAG_RIGHT_ID "mario.holdFlagRight"
#define MARIO_HOLD_FLAG_LEFT_ID "mario.holdFlagLeft"
#define MARIO_TURNING_SUPER_RIGHT_ID "mario.turningSuperRight"
#define MARIO_TURNING_LEFT_RIGHT_ID "mario.turningSuperLeft"
#define MARIO_DEATH_ID "mario.death"

class SpriteLoader {
public:
	static void loadMarioSprites();
	static void loadKoopaSprites();
	static void loadGoombaSprites();

	static void loadSprites();
};

void SpriteLoader::loadMarioSprites() {

}

void SpriteLoader::loadKoopaSprites() {

}

void SpriteLoader::loadGoombaSprites() {

}

void SpriteLoader::loadSprites() {
	loadMarioSprites();
	loadKoopaSprites();
	loadGoombaSprites();
}


#endif _SPRITELOADER_H_
