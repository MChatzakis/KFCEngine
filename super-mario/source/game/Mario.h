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
	using AnimatorsList = std::map<std::string, Animator*>;

	static Mario mario;

	Sprite* currSprite = nullptr;
	AnimatorsList animators;
	/*FrameRangeAnimator* animator_walkingRight = nullptr;
	FrameRangeAnimator* animator_walkingLeft = nullptr;

	MovingAnimator* animator_jumpRight = nullptr;
	MovingAnimator* animator_jumpLeft = nullptr;*/

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
	void jumpLeft();
	void jumpRight();
	void jump();
	void walkRight();
	void walkLeft();
	void backToIdle();

	void displayMarioWalkingRight_DEBUG(Bitmap target);

	void displayMario(Bitmap target);
	void displayMario(Bitmap target, const Rect& rect, const Clipper& clip);
	void Die();
	
	Animator* GetAnimator(std::string id);
	void AddAnimator(std::string id, Animator* animator);
	void StopAnimators();

	void AlignViewWin(TileLayer* currLayer);
};

Mario Mario::mario;

void Mario::backToIdle() {
	std::string id = currSprite->GetAnimationFilm()->GetId();

	if (id == MARIO_WALK_RIGHT_ID) {
		currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
		StopAnimators();
	}

	else if (id == MARIO_WALK_LEFT_ID) {
		currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);
		StopAnimators();
	}
}

Animator* Mario::GetAnimator(std::string id) {
	auto i = animators.find(id);
	return i != animators.end() ? i->second : nullptr;
}

void Mario::AddAnimator(std::string id, Animator* animator) {
	assert(!GetAnimator(id));
	animators.insert({ id, animator });
}

void Mario::initializeSprites() {
	currSprite = new Sprite(10, 250, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
	currSprite->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), currSprite));
	PrepareSpriteGravityHandler(gameMap->GetGrid(), currSprite);
	currSprite->GetGravityHandler().SetGravityAddicted(true);
	currSprite->Move(1, 0);
	SpriteManager::GetSingleton().Add(currSprite);
}

void Mario::initializeAnimators() {
	FrameRangeAnimator* animator_walkingRight = new FrameRangeAnimator();
	FrameRangeAnimator* animator_walkingLeft = new FrameRangeAnimator();
	MovingAnimator* animator_jumpRight = new MovingAnimator();
	MovingAnimator* animator_jumpLeft = new MovingAnimator();

	//Set on action

	//Walking Right
	animator_walkingRight->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const FrameRangeAnimation*>(&anim));
			FrameRange_Action(this->currSprite, animator, (const FrameRangeAnimation&)anim);
		}
	);

	//Walking left
	animator_walkingLeft->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const FrameRangeAnimation*>(&anim));
			FrameRange_Action(this->currSprite, animator, (const FrameRangeAnimation&)anim);
		}
	);

	//Jump right
	animator_jumpRight->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const MovingAnimation*>(&anim));
			Sprite_MoveAction(this->currSprite, (const MovingAnimation&)anim);
		}
	);

	//Jump left
	animator_jumpLeft->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const MovingAnimation*>(&anim));
			Sprite_MoveAction(this->currSprite, (const MovingAnimation&)anim);
		}
	);

	//Set on finish
	const Animator::OnFinish idleRight =
		[this](Animator* animator) {
		currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
	};

	const Animator::OnFinish idleLeft =
		[this](Animator* animator) {
		currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);
	};

	//animator_walkingRight->SetOnFinish(idleRight);
	//animator_walkingLeft->SetOnFinish(idleLeft);
	//animator_jumpRight->SetOnFinish(idleRight);
	//animator_jumpLeft->SetOnFinish(idleLeft);

	AddAnimator("walkRight", animator_walkingRight);
	AddAnimator("walkLeft", animator_walkingLeft);
	AddAnimator("jumpRight", animator_jumpRight);
	AddAnimator("jumpLeft", animator_jumpLeft);


}

void Mario::initialize() {
	initializeSprites();
	initializeAnimators();
}

void Mario::walkRight() {
	if (!(this->GetAnimator("walkRight")->HasFinished()) && currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_RIGHT_ID && currSprite->GetStateId() == "WALKING_STATE")
		return;

	currSprite->SetStateId("WALKING_STATE");
	FrameRangeAnimator* anim = ((FrameRangeAnimator*)GetAnimator("walkRight"));
	StopAnimators();
	FrameRangeAnimation* walkRight = new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 2, 2, 0, 120);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	anim->Start(walkRight, CurrTime());
}

void Mario::walkLeft() {
	if (!(this->GetAnimator("walkLeft")->HasFinished()) && currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_LEFT_ID && currSprite->GetStateId() == "WALKING_STATE")
		return;

	currSprite->SetStateId("WALKING_STATE");
	FrameRangeAnimator* anim = ((FrameRangeAnimator*)GetAnimator("walkLeft"));
	StopAnimators();
	FrameRangeAnimation* walkLeft = new FrameRangeAnimation(MARIO_WALK_LEFT_ID, 0, 2, 2, -2, 0, 120);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);
	anim->Start(walkLeft, CurrTime());
}

void Mario::runRight() {
	if (!(this->GetAnimator("walkRight")->HasFinished()) && currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_RIGHT_ID && currSprite->GetStateId() == "RUNNING_STATE")
		return;

	currSprite->SetStateId("RUNNING_STATE");
	FrameRangeAnimator* anim = ((FrameRangeAnimator*)GetAnimator("walkRight"));
	StopAnimators();
	FrameRangeAnimation* walkRight = new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, 4, 0, 80);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	//currSprite = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	anim->Start(walkRight, CurrTime());
	//animator_walkingRight->setAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, 3, 0, 15);
}

void Mario::runLeft() {
	if (!(this->GetAnimator("walkLeft")->HasFinished()) && currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_LEFT_ID && currSprite->GetStateId() == "RUNNING_STATE")
		return;

	currSprite->SetStateId("RUNNING_STATE");
	FrameRangeAnimator* anim = ((FrameRangeAnimator*)GetAnimator("walkLeft"));
	StopAnimators();
	FrameRangeAnimation* walkLeft = new FrameRangeAnimation(MARIO_WALK_LEFT_ID, 0, 2, 1, -4, 0, 80);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);
	anim->Start(walkLeft, CurrTime());
}

void Mario::jumpLeft() {
	MovingAnimator* anim = ((MovingAnimator*)GetAnimator("jumpLeft"));
	MovingAnimation* jumpLeft = new MovingAnimation(MARIO_JUMP_LEFT_ID, 8, 0, -4, 40);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_LEFT_ID), MARIO_JUMP_LEFT_ID);
	anim->Start(jumpLeft, CurrTime());
}

void Mario::jumpRight() {
	MovingAnimator* anim = ((MovingAnimator*)GetAnimator("jumpRight"));
	MovingAnimation* jumpRight = new MovingAnimation(MARIO_JUMP_RIGHT_ID, 8, 0, -4, 40);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);
	anim->Start(jumpRight, CurrTime());
}

void Mario::jump() {
	std::string id = currSprite->GetAnimationFilm()->GetId();
	
	if (currSprite->GetStateId() == "JUMP" )//|| */currSprite->GetGravityHandler().IsFalling())
		return;

	currSprite->GetGravityHandler().SetGravityAddicted(false);

	currSprite->SetStateId("JUMP");
	StopAnimators();
	if (id == MARIO_IDLE_RIGHT_ID || id == MARIO_WALK_RIGHT_ID) {
		jumpRight();
	}
	else if (id == MARIO_IDLE_LEFT_ID || id == MARIO_WALK_LEFT_ID) {
		jumpLeft();
	}

	currSprite->GetGravityHandler().SetGravityAddicted(true);
}

void Mario::displayMarioWalkingRight_DEBUG(Bitmap target) {
	//sprite_walkingRight->Display(target);
}

void Mario::displayMario(Bitmap target) {
	currSprite->Display(target);
}

void Mario::displayMario(Bitmap target, const Rect& rect, const Clipper& clip) {
	currSprite->Display(target, rect, clip);
}

void Mario::Die() {
	for (auto const& x : animators)
	{
		x.second->Destroy();
	}
	currSprite->Destroy();
}

void Mario::StopAnimators() {
	for (auto const& x : animators)
	{
		if (!x.second->HasFinished()) //if its running
			x.second->Stop();
	}
}

void Mario::AlignViewWin(TileLayer *currLayer) {
	Rect viewWin = currLayer->GetViewWindow();
	Point marioPos = currSprite->GetPosition();
	int mario_x = marioPos.x;
	int mario_y = marioPos.y;

	int viewWinCenter = viewWin.x + viewWin.w / 2;

	if (mario_x >= viewWinCenter) {
		//viewWin.x += 1;
		std::cout << "Mario Current CC: [" << mario_x << "," << mario_y << "]\n";
		std::cout << "ViewWin Center (x): [" << viewWinCenter << "]\n";
		currLayer->ScrollWithBoundsCheck(mario_x - viewWinCenter, 0);
	}
}

#endif _MARIO_H_