#ifndef _GOOMBA_H_
#define _GOOMBA_H_

#include <iostream>

#include <nlohmann/json.hpp>

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"

#include "../engine/AnimationFilmHolder.h"
#include "../engine/Animator.h"
#include "../engine/MovingAnimator.h"
#include "../engine/Timing.h"
#include "../engine/FrameRangeAnimator.h"

#include "./GameVars.h"

#define GOOMBA_DEATH_ID "goomba.death"
#define GOOMBA_WALK_ID "goomba.walk"


class Goomba {
private:
	int dx = 4;
	int direction = 1; //1 or -1
	int delay = 80;
	int deathDelay = 80;

	Sprite* sprite = nullptr;

	FrameRangeAnimator* goombaWalkAnimator = nullptr;
	FrameRangeAnimation* goombaWalkAnimation = nullptr;

	MovingAnimation* deathAnimation = nullptr; //todo
	MovingAnimation* deathByKoopaAnimation = nullptr; //todo
	MovingAnimator* deathAnimator = nullptr; //todo

	void createSprite(Point p);

	void createGoombaWalkAnimations();

public:
	Goomba(int _dx, int _dir, Point sp);

	Goomba(int _dx, int _dir, Point sp, int _del);

	Goomba(int _dx, int _dir, Point sp, int _del, int _ddel);

	Sprite* getSprite();

	void setSprite(Sprite* s);

	int getDx();

	void setDx(int _dx);

	int getDirection();

	void setDirection(int _dir);

	void destroyAnimators();

	void stopAnimators();

	void walk();

	void die();

	void dieAction();

	void dieByKoopaAction();

	MovingAnimator* getDeathAnimator();

	bool isDying();
};


class GoombaHolder {
private:
	static GoombaHolder holder;

	std::map<Sprite*, Goomba*>Goombas;

public:

	void CreateGoombaMap(nlohmann::json conf);

	void CreateGoombaMap(std::list<Point>point);

	void ErasePair_freeGoomba(Sprite* s);

	void Initialize(std::list<Point>points);

	void Initialize(nlohmann::json conf);

	static auto GetSingleton(void)->GoombaHolder&;
	static auto GetSingletonConst(void) -> const GoombaHolder&;

	std::list<Sprite*> GetGoombaSpritesList();

	std::list<Goomba*> GetGoombaClassList();

	std::map<Sprite*, Goomba*>& GetGoombaMap();

	void SetGoombaMap(std::map<Sprite*, Goomba*>gs);

	void WalkGoombas();

	Goomba* GetInstanceOf(Sprite* s);
};


#endif _GOOMBA_H_
