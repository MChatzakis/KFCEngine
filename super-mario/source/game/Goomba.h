#ifndef _GOOMBA_H_
#define _GOOMBA_H_

#include "../engine/Sprite.h"

#define GOOMBA_DEATH_ID "goomba.death"
#define GOOMBA_WALK_ID "goomba.walk"

class Goomba {
private:
    Sprite* sprite_walkingRight = nullptr;
    Sprite* sprite_walkingLeft = nullptr;
	Sprite* sprite_death = nullptr;

	FrameRangeAnimator* animator_walkingRight = nullptr;

	static Goomba goomba;

public:
    Goomba() {

	}

	static auto GetSingleton(void) -> Goomba& { return goomba; }
	static auto GetSingletonConst(void) -> const Goomba& { return goomba; }

	void initializeSprites();
	void initializeAnimators();

	void initialize();

	void runRight();

	void displayGoombaWalkingRight_DEBUG(Bitmap target);
};

Goomba Goomba::goomba;

void Goomba::initializeSprites() {
	sprite_walkingRight = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GOOMBA_WALK_ID), GOOMBA_WALK_ID);
	sprite_walkingLeft = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GOOMBA_WALK_ID), GOOMBA_WALK_ID);

	sprite_walkingRight = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GOOMBA_WALK_ID), GOOMBA_WALK_ID);
	sprite_walkingRight->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), sprite_walkingRight));
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
	
	sprite_walkingLeft = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GOOMBA_WALK_ID), GOOMBA_WALK_ID);

	SpriteManager::GetSingleton().Add(sprite_walkingRight);
	SpriteManager::GetSingleton().Add(sprite_walkingLeft);
	SpriteManager::GetSingleton().Add(sprite_death);
}

void Goomba::initializeAnimators() {
	animator_walkingRight = new FrameRangeAnimator();
	

	animator_walkingRight->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			FrameRange_Action(this->sprite_walkingRight, animator, (const FrameRangeAnimation&)anim);
		}
	);

	animator_walkingRight->SetOnFinish(
		[this](Animator* animator) {
			AnimatorManager::GetSingleton().MarkAsSuspended(animator_walkingRight);
		}
	);

	AnimatorManager::GetSingleton().Register(animator_walkingRight);
}

void Goomba::initialize() {
	initializeSprites();
	initializeAnimators();
}

void Goomba::runRight() {
	animator_walkingRight->Start(new FrameRangeAnimation(GOOMBA_WALK_ID, 0, 2, 3, 3, 0, 70), CurrTime());
	AnimatorManager::GetSingleton().MarkAsRunning(animator_walkingRight);
	//animator_walkingRight->setAnimation(GOOMBA_WALK_ID, 0, 2, 1, 3, 0, 15);
}

void Goomba::displayGoombaWalkingRight_DEBUG(Bitmap target) {
	sprite_walkingRight->Display(target);
}

#endif _GOOMBA_H_
