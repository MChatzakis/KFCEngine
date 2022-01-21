#ifndef _MARIO_H_
#define _MARIO_H_

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"
#include "../engine/AnimationFilmHolder.h"
#include "../engine/AnimatorManager.h"
#include "../engine/FrameRangeAnimator.h"
#include "../engine/Timing.h"

#include "./GameVars.h"

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

class Mario {

private:
	Sprite* sprite_idleRight = nullptr;
	Sprite* sprite_idleLeft = nullptr;
	Sprite* sprite_walkingRight = nullptr;
	Sprite* sprite_walkingLeft = nullptr;

	FrameRangeAnimator* animator_walkingRight = nullptr;

	static Mario mario;
public:

	Mario() {

	}

	static auto GetSingleton(void) -> Mario& { return mario; }
	static auto GetSingletonConst(void) -> const Mario& { return mario; }

	void initializeSprites();
	void initializeAnimators();

	void initialize();

	void runRight();

	void displayMarioWalkingRight_DEBUG(Bitmap target);
};

Mario Mario::mario;

void Mario::initializeSprites() {
	sprite_idleRight = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
	sprite_idleLeft = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);

	sprite_walkingRight = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	sprite_walkingRight->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), sprite_walkingRight));
	
	sprite_walkingLeft = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);

	SpriteManager::GetSingleton().Add(sprite_idleRight);
	SpriteManager::GetSingleton().Add(sprite_idleLeft);
	SpriteManager::GetSingleton().Add(sprite_walkingRight);
	SpriteManager::GetSingleton().Add(sprite_walkingLeft);
}


void Mario::initializeAnimators() {
	animator_walkingRight = new FrameRangeAnimator();
	

	animator_walkingRight->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			FrameRange_Action(this->sprite_walkingRight, animator, (const FrameRangeAnimation&)anim);
		}
	);

	animator_walkingRight->SetOnFinish(
		[this](Animator* animator) {
			//FrameRange_Action(this->sprite_walkingRight, animator, (const FrameRangeAnimation&)anim);
			animator->Stop();
		}
	);

	AnimatorManager::GetSingleton().Register(animator_walkingRight);
}

void Mario::initialize() {
	initializeSprites();
	initializeAnimators();
}


void Mario::runRight() {
	animator_walkingRight->Start(new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 100, 3, 0, 70), CurrTime());
	AnimatorManager::GetSingleton().MarkAsRunning(animator_walkingRight);
	//animator_walkingRight->setAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, 3, 0, 15);
}

void Mario::displayMarioWalkingRight_DEBUG(Bitmap target) {
	sprite_walkingRight->Display(target);
}

#endif _MARIO_H_