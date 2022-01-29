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
#define MARIO_JUMPING (currSprite->GetStateId() == "jumping_vertical_right" || currSprite->GetStateId() == "jumping_vertical_left" || currSprite->GetStateId() == "jumping_left" || currSprite->GetStateId() == "jumping_right")
#define MARIO_WALKING (currSprite->GetStateId() == "walking_right" || currSprite->GetStateId() == "walking_left")
#define MARIO_RUNNING (currSprite->GetStateId() == "running_right" || currSprite->GetStateId() == "running_left")
#define MARIO_IDLE (currSprite->GetStateId() == "idle_right" || currSprite->GetStateId() == "idle_left")

class Mario {

private:
	using AnimatorsList = std::map<std::string, Animator*>;
	using AnimationsList = std::map<std::string, Animation*>;

	static Mario mario;

	Sprite* currSprite = nullptr;
	AnimatorsList animators;
	AnimationsList animations;

public:

	Mario() {

	}

	static auto GetSingleton(void) -> Mario& { return mario; }
	static auto GetSingletonConst(void) -> const Mario& { return mario; }

	Sprite* GetCurrSprite();

	void initializeAnimations();
	void initializeSprites();
	void initializeAnimators();

	void initialize();

	void runRight();
	void runLeft();

	void jumpVerticalLeft();
	void jumpVerticalRight();
	void jumpVertical();

	void jumpRight();
	void jumpLeft();
	void jump();

	void walkRight();
	void walkLeft();

	void backToIdle();

	void displayMario(Bitmap target);
	void displayMario(Bitmap target, const Rect& rect, const Clipper& clip);
	
	void Die();

	Animator* GetAnimator(std::string id);
	void AddAnimator(std::string id, Animator* animator);
	void StopAnimators();

	Animation* GetAnimation(std::string id);
	void AddAnimation(std::string id, Animation* anim);

	void AlignViewWin(TileLayer* currLayer);
};

Mario Mario::mario;

Sprite* Mario::GetCurrSprite() {
	return currSprite;
}

void Mario::backToIdle() {
	if (MARIO_IDLE || MARIO_FALLING) /* || MARIO_JUMPING) || MARIO_FALLING || -> if we add that it jumps always in the same way*/
		return;

	std::string id = currSprite->GetStateId();
	StopAnimators(); //or in ifs for safety?

	if (id == "walking_right" || id == "running_right") {
		currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
		currSprite->SetStateId("idle_right");
	}
	else if (id == "walking_left" || id == "running_left") {
		currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);
		currSprite->SetStateId("idle_left");
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

Animation* Mario::GetAnimation(std::string id) {
	auto i = animations.find(id);
	return i != animations.end() ? i->second : nullptr;
}

void Mario::AddAnimation(std::string id, Animation* anim) {
	assert(!GetAnimation(id));
	animations.insert({ id, anim });
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
			//std::cout << "gtxs\n";
			//this->currSprite->SetStateId("falling_right"); //lathos
			//sprite->SetStateId("sdf");
			//sprite->Move(0, -1);
			return;
		}
	);

	currSprite->GetGravityHandler().SetOnStopFalling(
		[this]()
		{
			std::string id = this->currSprite->GetStateId();

			if (id == "falling_right") { //if animation finished or stopped
				this->currSprite->SetStateId("idle_right");
				this->currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
			}
			else if (id == "falling_left"){
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

void Mario::initializeAnimations() {
	/*AddAnimation("running_right", new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, 4, 0, 60));
	AddAnimation("running_left", new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, -4, 0, 60));
	AddAnimation("walking_right", new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, 2, 0, 120));
	AddAnimation("walking_left", new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, -2, 0, 120));
	AddAnimation("jumping_right", new MovingAnimation(MARIO_JUMP_RIGHT_ID, 17, 0, -4, 20)); //17 reps -> 16 calls of move -> 16*4 == 4 tiles
	AddAnimation("jumping_left", new MovingAnimation(MARIO_JUMP_LEFT_ID, 17, 0, -4, 20));
	AddAnimation("parabola_jumping_right", new FrameRangeAnimation(MARIO_JUMP_RIGHT_ID, 0, 0, 17, 2, -4, 20));*/

	AddAnimation("moving_right", new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, 2, 1, 0, 0, 0)); //set dx, dy, delay on functions
	AddAnimation("moving_left", new FrameRangeAnimation(MARIO_WALK_LEFT_ID, 0, 2, 1, 0, 0, 0));
	AddAnimation("vertical_jumping_right", new MovingAnimation(MARIO_JUMP_RIGHT_ID, 17, 0, 0, 0));
	AddAnimation("vertical_jumping_left", new MovingAnimation(MARIO_JUMP_LEFT_ID, 17, 0, 0, 0));
	AddAnimation("parabola_jumping_right", new FrameRangeAnimation(MARIO_JUMP_RIGHT_ID, 0, 0, 17, 0, 0, 0));
	AddAnimation("parabola_jumping_left", new FrameRangeAnimation(MARIO_JUMP_LEFT_ID, 0, 0, 17, 0, 0, 0));
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
			std::string id = this->currSprite->GetStateId();

			if (id == "jumping_vertical_right") {
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

	FrameRangeAnimator* parabola_jumping = new FrameRangeAnimator();

	parabola_jumping->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const FrameRangeAnimation*>(&anim));
			FrameRange_Action_DecreasingDY(this->currSprite, animator, (const FrameRangeAnimation&)anim);
		}
	);

	parabola_jumping->SetOnFinish(
		[this](Animator* animator) {
		std::string id = this->currSprite->GetStateId();

		if (id == "jumping_right") {
			this->currSprite->SetStateId("falling_right");
		}
		else {
			this->currSprite->SetStateId("falling_left");
		}

	}
	);

	parabola_jumping->SetOnStart(
		[this](Animator* animator) {

	}
	);

	AddAnimator("running", running);
	AddAnimator("jumping", jumping);
	AddAnimator("parabola_jumping", parabola_jumping);

}

void Mario::initialize() {
	initializeAnimations();
	initializeSprites();
	initializeAnimators();
}

void Mario::runRight() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_RIGHT_ID && */ currSprite->GetStateId() == "running_right"))
		return;

	currSprite->SetStateId("running_right");
	FrameRangeAnimator* running = (FrameRangeAnimator*) GetAnimator("running");
	
	StopAnimators();

	FrameRangeAnimation* runningRight = (FrameRangeAnimation*) GetAnimation("moving_right");
	runningRight->SetDx(4);
	runningRight->SetDelay(60);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);

	running->Start(runningRight, CurrTime());
}

void Mario::walkRight() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_RIGHT_ID && */ currSprite->GetStateId() == "walking_right"))
		return;

	currSprite->SetStateId("walking_right");
	FrameRangeAnimator* running = (FrameRangeAnimator*) GetAnimator("running");
	
	StopAnimators();
	
	FrameRangeAnimation* walkingRight = (FrameRangeAnimation*) GetAnimation("moving_right");
	walkingRight->SetDx(2);
	walkingRight->SetDelay(120);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);
	
	running->Start(walkingRight, CurrTime());
}

void Mario::walkLeft() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_LEFT_ID &&*/ currSprite->GetStateId() == "walking_left"))
		return;

	currSprite->SetStateId("walking_left");
	FrameRangeAnimator* running = (FrameRangeAnimator*) GetAnimator("running");
	
	StopAnimators();
	
	FrameRangeAnimation* walkingLeft = (FrameRangeAnimation*)GetAnimation("moving_left");
	walkingLeft->SetDx(-2);
	walkingLeft->SetDelay(120);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);
	
	running->Start(walkingLeft, CurrTime());
}

void Mario::runLeft() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_LEFT_ID &&*/ currSprite->GetStateId() == "running_left"))
		return;

	currSprite->SetStateId("running_left");
	FrameRangeAnimator* running = (FrameRangeAnimator*) GetAnimator("running");
	
	StopAnimators();
	
	FrameRangeAnimation* runningLeft = (FrameRangeAnimation*)GetAnimation("moving_left");
	runningLeft->SetDx(-4);
	runningLeft->SetDelay(60);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);
	
	running->Start(runningLeft, CurrTime());
}

void Mario::jumpVerticalLeft() {
	currSprite->SetStateId("jumping_vertical_left");

	MovingAnimator* jumping = (MovingAnimator*) GetAnimator("jumping");
	MovingAnimation* jumpingLeft = (MovingAnimation*)GetAnimation("vertical_jumping_left");
	
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_LEFT_ID), MARIO_JUMP_LEFT_ID);
	
	jumping->Start(jumpingLeft, CurrTime());
}

void Mario::jumpVerticalRight() {
	currSprite->SetStateId("jumping_vertical_right");

	MovingAnimator* jumping = (MovingAnimator*) GetAnimator("jumping");
	MovingAnimation* jumpingRight = (MovingAnimation*) GetAnimation("vertical_jumping_right");
	
	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);
	
	jumping->Start(jumpingRight, CurrTime());
}

void Mario::jumpRight() {
	currSprite->SetStateId("jumping_right");

	FrameRangeAnimator* parabola_jumping = (FrameRangeAnimator*)GetAnimator("parabola_jumping");
	FrameRangeAnimation* parabola_jumpingRight = (FrameRangeAnimation*)GetAnimation("parabola_jumping_right");
	parabola_jumpingRight->SetDx(2);
	parabola_jumpingRight->SetDy(-4);
	parabola_jumpingRight->SetDelay(20);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);

	parabola_jumping->Start(parabola_jumpingRight, CurrTime());
}

void Mario::jumpLeft() {
	currSprite->SetStateId("jumping_left");

	FrameRangeAnimator* jumping = (FrameRangeAnimator*)GetAnimator("parabola_jumping");
	FrameRangeAnimation* parabola_jumpingLeft = (FrameRangeAnimation*)GetAnimation("parabola_jumping_left");
	parabola_jumpingLeft->SetDx(-2);
	parabola_jumpingLeft->SetDy(-4);
	parabola_jumpingLeft->SetDelay(20);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_LEFT_ID), MARIO_JUMP_LEFT_ID);

	jumping->Start(parabola_jumpingLeft, CurrTime());
}

void Mario::jump() {
	if (MARIO_JUMPING || MARIO_FALLING)
		return;

	std::string spriteStateId = currSprite->GetStateId();
	StopAnimators();

	if (spriteStateId == "idle_right") {
		jumpVerticalRight();
	}
	else if (spriteStateId == "idle_left") {
		jumpVerticalLeft();
	}
	else if (spriteStateId == "walking_right") {
		jumpRight();
	}
	else if (spriteStateId == "running_right") {
		jumpRight();
	}
	else if (spriteStateId == "running_left") {
		jumpLeft();
	}
	else { //else if walking left
		jumpLeft();
	}
}

void Mario::jumpVertical() {
	std::string spriteStateId = currSprite->GetStateId();
	if (MARIO_JUMPING || MARIO_FALLING)//|| */currSprite->GetGravityHandler().IsFalling())
		return;

	//std::string id = currSprite->GetAnimationFilm()->GetId();
	StopAnimators();
	
	if (spriteStateId == "running_right" || spriteStateId == "walking_right" || spriteStateId == "idle_right") {
		jumpVerticalRight();
	}
	else /*if (id == MARIO_IDLE_LEFT_ID || id == MARIO_WALK_LEFT_ID)*/ {
		jumpVerticalLeft();
	}
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
		if (viewWin.x + viewWin.w < SCROLLABLE_TILE_COL * TILE_WIDTH) {
			currLayer->ScrollWithBoundsCheck(16, 0);
		}
	}
}

#endif _MARIO_H_