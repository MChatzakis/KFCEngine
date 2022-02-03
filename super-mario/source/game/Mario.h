#ifndef _MARIO_H_
#define _MARIO_H_

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"
#include "../engine/AnimationFilmHolder.h"
#include "../engine/AnimatorManager.h"
#include "../engine/FrameRangeAnimator.h"
#include "../engine/MovingAnimator.h"
#include "../engine/Timing.h"

#include <nlohmann/json.hpp>

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
#define MARIO_BOUNCE (currSprite->GetStateId() == "bouncing_right" || currSprite->GetStateId() == "bouncing_left" || currSprite->GetStateId() == "bouncing_vertical_right" || currSprite->GetStateId() == "bouncing_vertical_left")

#define MARIO_MOVING_RIGHT (/*currSprite->GetStateId() == "falling_right" ||*/ currSprite->GetStateId() == "walking_right" || currSprite->GetStateId() == "running_right" || currSprite->GetStateId() == "jumping_right")
#define MARIO_MOVING_LEFT (/*currSprite->GetStateId() == "falling_left" ||*/ currSprite->GetStateId() == "walking_left" || currSprite->GetStateId() == "running_left" || currSprite->GetStateId() == "jumping_left")


class Mario {

private:
	using AnimatorsList = std::map<std::string, Animator*>;
	using AnimationsList = std::map<std::string, Animation*>;

	static Mario mario;

	Sprite* currSprite = nullptr;

	AnimatorsList animators;
	AnimationsList animations;

	nlohmann::json conf;

	int score = 0;
	int totalCoins = 0;
	int totalLifes = 3;

public:

	Mario() {

	}

	static auto GetSingleton(void)->Mario&;
	static auto GetSingletonConst(void) -> const Mario&;

	Sprite* GetCurrSprite();

	void initializeAnimations();
	void initializeSprites();
	void initializeAnimators();

	void initialize(nlohmann::json _c);

	void runRight();
	void runLeft();

	void jumpVerticalLeft();
	void jumpVerticalRight();

	void jumpRight();
	void jumpLeft();
	void jump();

	void smallJump();
	void smallJumpVerticalLeft();
	void smallJumpVerticalRight();
	void smallJumpRight();
	void smallJumpLeft();

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

	void setScore(int _s);
	int getScore();
	void increaseScoreBy(int by);

	void setTotalLifes(int _tl);
	int getTotalLifes();
	void decreaseLifes();

	void setCoins(int _c);
	int getCoins();
	void increaseCoinsBy(int by);

	void EvaluateDeathAction();
	void Respawn();
};

#endif _MARIO_H_