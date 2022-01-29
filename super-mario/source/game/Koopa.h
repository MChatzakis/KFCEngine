#ifndef _KOOPA_H_
#define _KOOPA_H_

#include <iostream>

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


class Koopa {
private:
	int dx = 4;
	int direction = 1; //1 or -1
	int delay = 80;

	Sprite* sprite = nullptr;

	FrameRangeAnimator* koopaWalkAnimator = nullptr; //ok
	FrameRangeAnimation* koopaWalkAnimation = nullptr;

	MovingAnimator* greenKoopaShellAnimator = nullptr;
	MovingAnimation* greenKoopaShellAnimation = nullptr;

	Animation* deathAnimation = nullptr; //todo
	Animator* deathAnimator = nullptr; //todo

	void createSprite(Point p) {
		if (direction > 0) {
			sprite = new Sprite(p.x, p.y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_RIGHT_ID), GREEN_KOOPA_WALK_RIGHT_ID);
			//sprite->SetStateId("falling_right");
		}
		else {
			sprite = new Sprite(p.x, p.y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_LEFT_ID), GREEN_KOOPA_WALK_LEFT_ID);
			//sprite->SetStateId("falling_left");
		}

		sprite->SetZorder(2);

		sprite->SetMover(
			[this](const Rect& r, int* dx, int* dy) {
				assert(r == this->sprite->GetBox());
				gameMap->GetGrid()->FilterGridMotion(r, dx, dy);
				if (*dx || *dy)
					this->sprite->SetHasDirectMotion(true).Move(*dx, *dy).SetHasDirectMotion(false);
				else {
					this->setDirection(-1 * this->getDirection());
				}
			}
		);

		PrepareSpriteGravityHandler(gameMap->GetGrid(), sprite);

		sprite->GetGravityHandler().SetOnStartFalling(
			[this]()
			{
				return;
			}
		);

		sprite->GetGravityHandler().SetOnStopFalling(
			[this]()
			{
				return;
			}
		);

		sprite->GetGravityHandler().SetGravityAddicted(true);
		//sprite->Move(-1, 0);

		//SpriteManager::GetSingleton().Add(sprite);
	}

	void createKoopaWalkAnimations() {
		koopaWalkAnimator = new FrameRangeAnimator();

		koopaWalkAnimator->SetOnAction(
			[this](Animator* animator, const Animation& anim) {
				assert(dynamic_cast<const FrameRangeAnimation*>(&anim));
				FrameRange_Action(this->sprite, animator, (const FrameRangeAnimation&)anim);
			}
		);

		koopaWalkAnimator->SetOnFinish(
			[this](Animator* animator) {

			}
		);

		koopaWalkAnimator->SetOnStart(
			[this](Animator* animator) {

			}
		);

		if (direction > 0) {
			koopaWalkAnimation = new FrameRangeAnimation(GREEN_KOOPA_WALK_RIGHT_ID, 0, 1, 2, dx, 0, delay);
		}
		else {
			koopaWalkAnimation = new FrameRangeAnimation(GREEN_KOOPA_WALK_LEFT_ID, 0, 1, 2, -dx, 0, delay);
		}
	}

public:
	Koopa(int _dx, int _dir, Point sp) {
		direction = _dir;
		dx = _dx;

		createSprite(sp);
		createKoopaWalkAnimations();
	}

	Sprite* getSprite() {
		return sprite;
	}

	void setSprite(Sprite* s) {
		sprite = s;
	}

	int getDx() {
		return dx;
	}

	void setDx(int _dx) {
		dx = _dx;
	}

	int getDirection() {
		return direction;
	}

	void setDirection(int _dir) {
		//direction = _dir;

		direction = _dir;
		koopaWalkAnimation->SetDx(dx * direction);

		if (direction > 0) {
			//sprite->SetStateId("running_right");
			sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_RIGHT_ID), GREEN_KOOPA_WALK_RIGHT_ID);

		}
		else {
			//sprite->SetStateId("running_left");
			sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_LEFT_ID), GREEN_KOOPA_WALK_LEFT_ID);

		}

	}

	void changeDirection() {

		direction *= -1;

		if (direction > 0) {
			//sprite->SetStateId("running_right");
			sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_RIGHT_ID), GREEN_KOOPA_WALK_RIGHT_ID);
		}
		else {
			//sprite->SetStateId("running_left");
			sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_LEFT_ID), GREEN_KOOPA_WALK_LEFT_ID);
		}
		
		koopaWalkAnimation->SetDx(dx*direction);

	}

	void walk() {

		if ((!(koopaWalkAnimator->HasFinished())))
			return;

		koopaWalkAnimator->Start(koopaWalkAnimation, CurrTime());
	}

};


class KoopaHolder {
private:
	static KoopaHolder holder;

	/*std::list<Koopa*>koopas; //two lists corresponds to spritelist
	std::list<Sprite*>koopasSprites;*/

	std::map<Sprite*, Koopa*>Koopas;

public:

	void createKoopasMap(std::list<Point>point) {
		for (auto p : point) {
			Koopa* k = new Koopa(1, -1, p);
			Sprite* s = k->getSprite();

			Koopas[s] = k;
			SpriteManager::GetSingleton().Add(s);
		}
	}

	/*void createKoopaSprites() {

		//keep em in a list
		for (Koopa* g : koopas) {
			koopasSprites.push_back(g->getSprite());
		}

		//add em in the sprite manager
		for (Sprite* s : koopasSprites) {
			SpriteManager::GetSingleton().Add(s);
		}

		//add em in the map
		SpriteManager::GetSingleton().CreateTypeList("koopa", koopasSprites);
	}*/

	void initialize(std::list<Point>point) {
		createKoopasMap(point);
	}

	static auto GetSingleton(void) -> KoopaHolder& { return holder; }
	static auto GetSingletonConst(void) -> const KoopaHolder& { return holder; }

	/*std::list<Sprite*> getKoopasSprites() {
		return koopasSprites;
	}
	std::list<Koopa*> getKoopas() {
		return koopas;
	}*/

	void ErasePair(Sprite *s) {
		Koopas.erase(s);
	}

	std::map<Sprite*, Koopa*>& GetKoopaMap() {
		return Koopas;
	}

	void setKoopaMap(std::map<Sprite*, Koopa*>m) {
		Koopas = std::map<Sprite*, Koopa*>(m);
	}

	std::list<Sprite*> GetKoopaSpritesList() {
		std::list<Sprite*>l;
		for (auto e : Koopas) {
			l.push_back(e.first);
		}
		return l;
	}

	std::list<Koopa*> GetKoopaClassList() {
		std::list<Koopa*>l;
		for (auto e : Koopas) {
			l.push_back(e.second);
		}
		return l;
	}

	void WalkKoopas() {
		for (auto g : Koopas) {
			g.second->walk();
		}
	}
};

KoopaHolder KoopaHolder::holder;

#endif _KOOPA_H_