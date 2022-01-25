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

#define MARIO_FALLING (currSprite->GetStateId() == "falling_right" || currSprite->GetStateId() == "falling_left")
#define MARIO_JUMPING (currSprite->GetStateId() == "jumping_vertical_right" || currSprite->GetStateId() == "jumping_vertical_left")
#define MARIO_WALKING (currSprite->GetStateId() == "walking_right" || currSprite->GetStateId() == "walking_left")
#define MARIO_RUNNING (currSprite->GetStateId() == "running_right" || currSprite->GetStateId() == "running_left")
#define MARIO_IDLE (currSprite->GetStateId() == "idle_right" || currSprite->GetStateId() == "idle_left")

class Mario {

private:
	using AnimatorsList = std::map<std::string, Animator*>;

	static Mario mario;

	Sprite* currSprite = nullptr;
	AnimatorsList animators;

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
		currSprite->SetStateId("idle_right");
		StopAnimators();
	}
	else if (id == MARIO_WALK_LEFT_ID) {
		currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);
		currSprite->SetStateId("idle_left");
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

	currSprite = new Sprite(320, 180, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
	//currSprite->SetStateId("idle_right");
	currSprite->SetStateId("falling_right");

	currSprite->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), currSprite));

	PrepareSpriteGravityHandler(gameMap->GetGrid(), currSprite);

	currSprite->GetGravityHandler().SetOnStartFalling(
		[this]()
		{
			std::cout << "gtxs\n";
			//this->currSprite->SetStateId("falling_right"); //lathos
			//sprite->SetStateId("sdf");
			//sprite->Move(0, -1);
			return;
		}
	);

	currSprite->GetGravityHandler().SetOnStopFalling(
		[this]()
		{
			if (this->currSprite->GetStateId() == "falling_right") {
				this->currSprite->SetStateId("idle_right");
				this->currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
			}
			else if (this->currSprite->GetStateId() == "falling_left"){
				this->currSprite->SetStateId("idle_left");
				this->currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);

			}

			return;
		}
	);

	currSprite->GetGravityHandler().SetGravityAddicted(true);
	currSprite->Move(1, 0);
	
	SpriteManager::GetSingleton().Add(currSprite);
}

void Mario::initializeAnimators() {

	FrameRangeAnimator* running = new FrameRangeAnimator();

	running->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const FrameRangeAnimation*>(&anim));
			FrameRange_Action(this->currSprite, animator, (const FrameRangeAnimation&)anim);
		}
	);

	running->SetOnFinish(
		[this](Animator* animator) {

		}
	);

	running->SetOnStart(
		[this](Animator* animator) {

		}
	);

	MovingAnimator* jumping = new MovingAnimator();

	jumping->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const MovingAnimation*>(&anim));
			Sprite_MoveAction(this->currSprite, (const MovingAnimation&)anim);
			//this->currSprite->SetHasDirectMotion(true).Move(((const MovingAnimation&)anim).GetDx(), ((const MovingAnimation&)anim).GetDy()).SetHasDirectMotion(false);
		}
	);

	jumping->SetOnFinish(
		[this](Animator* animator) {
			if (this->currSprite->GetTypeId() == MARIO_JUMP_RIGHT_ID) {
				this->currSprite->SetStateId("falling_right");
			}
			else{
				this->currSprite->SetStateId("falling_left");
			}
			
		}
	);

	jumping->SetOnStart(
		[this](Animator* animator) {

		}
	);

	AddAnimator("running", running);
	AddAnimator("jumping", jumping);

}

void Mario::initialize() {
	initializeSprites();
	initializeAnimators();
}

void Mario::runRight() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(this->GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_RIGHT_ID && */ currSprite->GetStateId() == "running_right"))
		return;

	currSprite->SetStateId("running_right");
	FrameRangeAnimator* running = ((FrameRangeAnimator*)GetAnimator("running"));
	
	StopAnimators();

	FrameRangeAnimation* runningRight = new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, 4, 0, 60);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);

	running->Start(runningRight, CurrTime());
}

void Mario::walkRight() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(this->GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_RIGHT_ID && */ currSprite->GetStateId() == "walking_right"))
		return;

	currSprite->SetStateId("walking_right");
	FrameRangeAnimator* running = ((FrameRangeAnimator*)GetAnimator("running"));
	
	StopAnimators();
	
	FrameRangeAnimation* walkingRight = new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 2, 2, 0, 120);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	
	running->Start(walkingRight, CurrTime());
}

void Mario::walkLeft() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(this->GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_LEFT_ID &&*/ currSprite->GetStateId() == "walking_left"))
		return;

	currSprite->SetStateId("walking_left");
	FrameRangeAnimator* running = ((FrameRangeAnimator*)GetAnimator("running"));
	
	StopAnimators();
	
	FrameRangeAnimation* walkingLeft = new FrameRangeAnimation(MARIO_WALK_LEFT_ID, 0, 2, 2, -2, 0, 120);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);
	
	running->Start(walkingLeft, CurrTime());
}

void Mario::runLeft() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(this->GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_LEFT_ID &&*/ currSprite->GetStateId() == "running_left"))
		return;

	currSprite->SetStateId("running_left");
	FrameRangeAnimator* running = ((FrameRangeAnimator*)GetAnimator("running"));
	
	StopAnimators();
	
	FrameRangeAnimation* runningLeft = new FrameRangeAnimation(MARIO_WALK_LEFT_ID, 0, 2, 1, -4, 0, 60);
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);
	
	running->Start(runningLeft, CurrTime());
}

void Mario::jumpLeft() {
	currSprite->SetStateId("jumping_vertical_left");

	MovingAnimator* jumping = ((MovingAnimator*)GetAnimator("jumping"));
	MovingAnimation* jumpingLeft = new MovingAnimation(MARIO_JUMP_LEFT_ID, 8, 0, -4, 40);
	
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_LEFT_ID), MARIO_JUMP_LEFT_ID);
	
	jumping->Start(jumpingLeft, CurrTime());
}

void Mario::jumpRight() {
	currSprite->SetStateId("jumping_vertical_right");

	MovingAnimator* jumping = ((MovingAnimator*)GetAnimator("jumping"));
	MovingAnimation* jumpingRight = new MovingAnimation(MARIO_JUMP_RIGHT_ID, 20, 0, -4, 40);
	
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);
	
	jumping->Start(jumpingRight, CurrTime());
}

void Mario::jump() {
	std::string spriteStateId = currSprite->GetStateId();
	if (MARIO_JUMPING || MARIO_FALLING)//|| */currSprite->GetGravityHandler().IsFalling())
		return;

	//std::string id = currSprite->GetAnimationFilm()->GetId();
	StopAnimators();
	
	if (spriteStateId == "running_right" || spriteStateId == "walking_right" || spriteStateId == "idle_right") {
		jumpRight();
	}
	else /*if (id == MARIO_IDLE_LEFT_ID || id == MARIO_WALK_LEFT_ID)*/ {
		jumpLeft();
	}
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

void Mario::AlignViewWin(TileLayer* currLayer) {
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