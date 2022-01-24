#ifndef _MARIO_H_
#define _MARIO_H_

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"
#include "../engine/AnimationFilmHolder.h"
#include "../engine/AnimatorManager.h"
#include "../engine/FrameRangeAnimator.h"
#include "../engine/MovingAnimator.h"
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

enum MarioState {
	MARIO_IDLE_RIGHT,
	MARIO_IDLE_LEFT,
	MARIO_RUNNING_RIGHT,
	MARIO_RUNNING_LEFT
};

class Mario {

private:
	Sprite* sprite_idleRight = nullptr;
	Sprite* sprite_idleLeft = nullptr;
	Sprite* sprite_walkingLeft = nullptr;
	Sprite* sprite_walkingRight = nullptr;



	static Mario mario;

	Sprite* currSprite = nullptr;

	FrameRangeAnimator* animator_walkingRight = nullptr;
	FrameRangeAnimator* animator_walkingLeft = nullptr;

	MovingAnimator* animator_jumpRight = nullptr;
	MovingAnimator* animator_jumpLeft = nullptr;

public:

	Mario() {

	}

	static auto GetSingleton(void) -> Mario& { return mario; }
	static auto GetSingletonConst(void) -> const Mario& { return mario; }

	void initializeSprites();
	void initializeAnimators();

	void initialize();

	void runRight();
	void runLeft();

	void displayMarioWalkingRight_DEBUG(Bitmap target);

	void displayMario(Bitmap target);
	void displayMario(Bitmap target, const Rect& rect, const Clipper& clip);
};

Mario Mario::mario;

void Mario::initializeSprites() {
	sprite_idleRight = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
	sprite_idleLeft = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);

	sprite_walkingRight = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	sprite_walkingRight->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), sprite_walkingRight));

	currSprite = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
	currSprite->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), currSprite));
	/*sprite_walkingRight->GetQuantizer().SetMover(
		[this](const Rect& r, int* dx, int* dy) {
			GridUtilities::FilterGridMotion(r, dx, dy);
		}
	);*/
	/*sprite_walkingRight->GetQuantizer().SetMover(
		[this](const Rect& r, int* dx, int* dy) {
		this->GetSingleton().sprite_walkingRight->SetPos(r.x + *dx, r.y + *dy);
			//r.x += *dx;
			//r.y += *dy;

		}
	);*/

	sprite_walkingLeft = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);

	SpriteManager::GetSingleton().Add(sprite_idleRight);
	SpriteManager::GetSingleton().Add(sprite_idleLeft);
	SpriteManager::GetSingleton().Add(sprite_walkingRight);
	SpriteManager::GetSingleton().Add(sprite_walkingLeft);
}


void Mario::initializeAnimators() {
	animator_walkingRight = new FrameRangeAnimator();
	animator_walkingLeft = new FrameRangeAnimator();
	animator_jumpRight = new MovingAnimator();
	animator_jumpLeft = new MovingAnimator();

	animator_walkingRight->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			FrameRange_Action(this->currSprite, animator, (const FrameRangeAnimation&)anim);
		}
	);

	animator_walkingRight->SetOnFinish(
		[this](Animator* animator) {
			//AnimatorManager::GetSingleton().MarkAsSuspended(animator_walkingRight);
			currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
		}
	);

	animator_walkingLeft->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			FrameRange_Action(this->currSprite, animator, (const FrameRangeAnimation&)anim);
		}
	);

	animator_walkingLeft->SetOnFinish(
		[this](Animator* animator) {
			//AnimatorManager::GetSingleton().MarkAsSuspended(animator_walkingRight);
			currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);
		}
	);

	/*animator_walkingRight = new FrameRangeAnimator();
	AnimatorManager::GetSingleton().Register(animator_walkingRight);*/

}


void Mario::initialize() {
	initializeSprites();
	initializeAnimators();
}


void Mario::runRight() {
	FrameRangeAnimation* walkRight = new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 4, 4, 0, 40);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	//currSprite = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	animator_walkingRight->Start(walkRight, CurrTime());
	//AnimatorManager::GetSingleton().MarkAsRunning(animator_walkingRight);
	//animator_walkingRight->setAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, 3, 0, 15);
}

void Mario::runLeft() {
	FrameRangeAnimation* walkLeft = new FrameRangeAnimation(MARIO_WALK_LEFT_ID, 0, 2, 4, -4, 0, 40);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);
	animator_walkingLeft->Start(walkLeft, CurrTime());
}

void Mario::displayMarioWalkingRight_DEBUG(Bitmap target) {
	sprite_walkingRight->Display(target);
}

void Mario::displayMario(Bitmap target) {
	currSprite->Display(target);
}

void Mario::displayMario(Bitmap target,const Rect& rect, const Clipper& clip) {
	currSprite->Display(target, rect, clip);
}


#endif _MARIO_H_