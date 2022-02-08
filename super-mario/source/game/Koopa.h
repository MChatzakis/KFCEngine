#ifndef _KOOPA_H_
#define _KOOPA_H_

#include <iostream>

#include <nlohmann/json.hpp>

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"

#include "../engine/AnimationFilmHolder.h"
#include "../engine/Animator.h"
#include "../engine/Timing.h"
#include "../engine/FrameRangeAnimator.h"
#include "../engine/MovingAnimator.h"

#include "./GameVars.h"

#define GREEN_KOOPA_WALK_RIGHT_ID "greenKoopa.walkRight"
#define GREEN_KOOPA_WALK_LEFT_ID "greenKoopa.walkLeft"
#define GREEN_KOOPA_SHELL_ID "greenKoopa.shell"
#define GREEN_KOOPA_DEATH_ID "greenKoopa.death"

enum KoopaState {
	WALKER,
	SHELL
};

class Koopa {
private:
	int dx = 4;
	int direction = 1; //1 or -1
	int delay = 80;

	int shellDx = 4;
	int shellDelay = 10;

	KoopaState state = WALKER;
	bool isAtShellStartingState = false;

	Sprite* sprite = nullptr;

	FrameRangeAnimator* koopaWalkAnimator = nullptr;
	FrameRangeAnimation* koopaWalkAnimation = nullptr;

	MovingAnimator* greenKoopaShellAnimator = nullptr;
	MovingAnimation* greenKoopaShellAnimation = nullptr;

	void createSprite(Point p);

	void createKoopaWalkAnimations();
	void createKoopaShellAnimations();

public:
	Koopa(int _dx, int _dir, Point sp);

	Koopa(int _dx, int _dir, Point sp, int _del);

	Koopa(int _dx, int _dir, Point sp, int _del, int _sdx, int _sdl);

	Sprite* getSprite();

	void setSprite(Sprite* s);

	void setState(KoopaState _s);

	KoopaState getState();

	int getDx();

	void setDx(int _dx);

	int getDirection();

	void setDirection(int _dir);

	void changeDirection();

	void walk();

	void transformToShell();

	void stopAnimators();

	bool getIsAtShellStartingState();

	void evaluateStartingShellAction(int x);

	void die();
	void destroyAnimators();

};


class KoopaHolder {
private:
	static KoopaHolder holder;

	std::map<Sprite*, Koopa*>Koopas;

public:

	void CreateKoopasMap(nlohmann::json conf);

	void CreateKoopasMap(std::list<Point>point);

	void Initialize(std::list<Point>point);

	void Initialize(nlohmann::json conf);

	static auto GetSingleton(void)->KoopaHolder&;
	static auto GetSingletonConst(void) -> const KoopaHolder&;

	void ErasePair(Sprite* s);

	std::map<Sprite*, Koopa*>& GetKoopaMap();

	void setKoopaMap(std::map<Sprite*, Koopa*>m);

	std::list<Sprite*> GetKoopaSpritesList();

	std::list<Koopa*> GetKoopaClassList();

	void WalkKoopas();

	Koopa* GetInstanceOf(Sprite* s);
		
};


#endif _KOOPA_H_