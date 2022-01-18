#ifndef _MARIO_H_
#define _MARIO_H_


#include "../engine/Sprite.h"
#include "../engine/AnimationFilmHolder.h"

#include "./GameVars.h"

#define MARIO_IDLE_RIGHT_ID "mario.idleRight"

class Mario {

private:
	Sprite* marioSprite_standingRight;

public:

	Mario() {
		initSprite();
	}

	void move() {
		marioSprite_standingRight->Display(al_get_backbuffer(display));
		marioSprite_standingRight->MoveOLD(1, 0);
	}

	void initSprite() {
		marioSprite_standingRight = new Sprite(10, 380, (AnimationFilm *)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
		marioSprite_standingRight->Display(al_get_backbuffer(display));

	}
	
};

#endif _MARIO_H_