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

	void destroyAnimators() {
		//if (!goombaWalkAnimator->HasFinished()) {
		//goombaWalkAnimator->Stop();
		//}

		//if (!deathAnimator->HasFinished()) {
		//deathAnimator->Stop();
		//}
		goombaWalkAnimator->Destroy();
		deathAnimator->Destroy();
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

	std::map<Sprite*, Goomba*>Goombas;

public:

	void CreateGoombaMap(std::list<Point>point) {
		for (auto p : point) {
			Goomba* g = new Goomba(1, 1, p);
			Sprite* s = g->getSprite();

			Goombas[s] = g;

			SpriteManager::GetSingleton().Add(s);
		}
	}

	void ErasePair_freeGoomba(Sprite* s) {
		Goomba* gToDel = Goombas[s];
		Goombas.erase(s);
		//delete gToDel; //exception when enabled
	}

	void Initialize(std::list<Point>points) {
		//createGoombas(point);
		//createGoombaSprites();
		CreateGoombaMap(points);
	}

	static auto GetSingleton(void) -> GoombaHolder& { return holder; }
	static auto GetSingletonConst(void) -> const GoombaHolder& { return holder; }

	std::list<Sprite*> GetGoombaSpritesList() {
		std::list<Sprite*>l;
		for (auto e : Goombas) {
			l.push_back(e.first);
		}
		return l;
	}

	std::list<Goomba*> GetGoombaClassList() {
		std::list<Goomba*>l;
		for (auto e : Goombas) {
			l.push_back(e.second);
		}
		return l;
	}

	std::map<Sprite*, Goomba*>& GetGoombaMap() {
		return Goombas;
	}

	void SetGoombaMap(std::map<Sprite*, Goomba*>gs) {
		Goombas = std::map<Sprite*, Goomba*>(gs);
	}

	void WalkGoombas() {
		for (auto g : Goombas) {
			g.second->walk();
		}
	}

	Goomba* GetInstanceOf(Sprite* s) {
		return Goombas[s];
	}
};

GoombaHolder GoombaHolder::holder;

#endif _GOOMBA_H_
