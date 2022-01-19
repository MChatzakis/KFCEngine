#ifndef _MARIO_H_
#define _MARIO_H_

#include "../engine/Sprite.h"
#include "../engine/AnimationFilmHolder.h"

#include "./GameVars.h"

#define MARIO_IDLE_RIGHT_ID "mario.idleRight"
#define MARIO_IDLE_LEFT "mario.idleLeft"
#define MARIO_WALK_RIGHT_ID "mario.walkRight"
#define MARIO_WALK_LEFT_ID "mario.walkLeft"
#define MARIO_JUMP_RIGHT_ID "mario.jumpRight"
#define MARIO_JUMP_LEFT_ID "mario.jumpLeft"
#define MARIO_STOP_WALKING_RIGHT_ID "mario.stopWalkingRight"
#define MARIO_STOP_WALKING_LEFT_ID "mario.stopWalkingLeft"
#define MARIO_UNKOWN_RIGHT_ID "mario.unknownRight"
#define MARIO_UNKOWN_LEFT_ID "mario.unknownLeft"
#define MARIO_HOLD_FLAG_RIGHT_ID "mario.holdFlagRight"
#define MARIO_HOLD_FLAG_LEFT_ID "mario.HoldFlagLeft"
#define MARIO_TURNING_SUPER_RIGHT_ID "mario.turningSuperRight"
#define MARIO_TURNING_LEFT_RIGHT_ID "mario.turningSuperLeft"
#define MARIO_DEATH_ID "mario.death"

class Mario {

private:
	Sprite* sprite_idleRight;
	Sprite* sprite_idleLeft;
	
	static Mario mario;
public:

	Mario() {
		
	}

	/*void move() {
		marioSprite_standingRight->Display(al_get_backbuffer(display));
		marioSprite_standingRight->MoveOLD(1, 0);
	}

	void initSprite() {
		marioSprite_standingRight = new Sprite(10, 380, (AnimationFilm *)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
		marioSprite_standingRight->Display(al_get_backbuffer(display));
	}*/
	
	void initializeSprites();


};

Mario Mario::mario;

#endif _MARIO_H_