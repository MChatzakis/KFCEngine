#ifndef _GOOMBA_H_
#define _GOOMBA_H_

#include <iostream>

#include "../engine/Sprite.h"
#include "../engine/SpriteManager.h"

#include "../engine/AnimationFilmHolder.h"
#include "../engine/Animator.h"
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

	Sprite* sprite = nullptr;

	FrameRangeAnimator* goombaWalkAnimator = nullptr;
	FrameRangeAnimation* goombaWalkAnimation = nullptr;

	Animation* deathAnimation = nullptr; //todo
	Animator* deathAnimator = nullptr; //todo


	void createSprite(Point p) {
		sprite = new Sprite(p.x, p.y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GOOMBA_WALK_ID), GOOMBA_WALK_ID);

		//sprite->SetStateId("falling");
		sprite->SetZorder(1);
		sprite->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), sprite));
		sprite->SetMover(
			[this](const Rect& r, int* dx, int* dy) {
				// the r is actually always the sprite->GetBox():
				assert(r == this->sprite->GetBox());
				//std::cout << "dx before: " << *dx << "\n";
				gameMap->GetGrid()->FilterGridMotion(r, dx, dy);
				//std::cout << "dx after: " << *dx << "\n";
				//TriggerScrollUtilities::FilterGridMotion(gridLayer, r, dx, dy);
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
				/*if (this->sprite->GetStateId() == "falling_right") {
					this->sprite->SetStateId("idle_right");
					this->sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
				}
				else if (this->sprite->GetStateId() == "falling_left") {
					this->sprite->SetStateId("idle_left");
					this->sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_LEFT_ID), MARIO_IDLE_LEFT_ID);

				}*/

				return;
			}
		);

		sprite->GetGravityHandler().SetGravityAddicted(true);
		//sprite->Move(1, 0);

		//SpriteManager::GetSingleton().Add(sprite);
	}

	void createGoombaWalkAnimations() {
		goombaWalkAnimator = new FrameRangeAnimator();

		goombaWalkAnimator->SetOnAction(
			[this](Animator* animator, const Animation& anim) {
				assert(dynamic_cast<const FrameRangeAnimation*>(&anim));
				FrameRange_Action(this->sprite, animator, (const FrameRangeAnimation&)anim);
			}
		);

		goombaWalkAnimator->SetOnFinish(
			[this](Animator* animator) {

			}
		);

		goombaWalkAnimator->SetOnStart(
			[this](Animator* animator) {

			}
		);

		goombaWalkAnimation = new FrameRangeAnimation(GOOMBA_WALK_ID, 0, 1, 2, dx * direction, 0, delay);
	}

public:
	Goomba(int _dx, int _dir, Point sp) {
		direction = _dir;
		dx = _dx;

		createSprite(sp);
		createGoombaWalkAnimations();
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
		direction = _dir;
		goombaWalkAnimation->SetDx(dx * direction);

		/*if (direction > 0) {
			sprite->SetStateId("running_right");
		}
		else {
			sprite->SetStateId("running_left");
		}*/
	}

	void walk() {

		if ((!(goombaWalkAnimator->HasFinished())/* && currSprite->GetStateId() == "running_right")*/))
			return;

		goombaWalkAnimator->Start(goombaWalkAnimation, CurrTime());
	}

};


class GoombaHolder {
private:
	static GoombaHolder holder;

	std::list<Goomba*>goombas; //two lists corresponds to spritelist
	std::list<Sprite*>goombasSprites;

public:

	void createGoombas(std::list<Point>point) {
		for (auto p : point) {
			goombas.push_back(new Goomba(1, 1, p));
		}
	}

	void createGoombaSprites() {

		//keep em in a list
		for (Goomba* g : goombas) {
			goombasSprites.push_back(g->getSprite());
		}

		//add em in the sprite manager
		for (Sprite* s : goombasSprites) {
			SpriteManager::GetSingleton().Add(s);
		}

		//add em in the map
		SpriteManager::GetSingleton().CreateTypeList("goomba", goombasSprites);
	}

	void initialize(std::list<Point>point) {
		createGoombas(point);
		createGoombaSprites();
	}

	static auto GetSingleton(void) -> GoombaHolder& { return holder; }
	static auto GetSingletonConst(void) -> const GoombaHolder& { return holder; }

	std::list<Sprite*> getGoombasSprites() {
		return goombasSprites;
	}
	std::list<Goomba*> getGoombas() {
		return goombas;
	}

	void setGoombasSprites(std::list<Sprite*>sprs) {
		goombasSprites = std::list<Sprite*>(sprs);
	}
	void setGoombas(std::list<Goomba*>gs) {
		goombas = std::list<Goomba*>(gs);
	}

	void walkGoombas() {
		for (auto g : goombas) {
			g->walk();
		}
	}
};

GoombaHolder GoombaHolder::holder;

#endif _GOOMBA_H_
