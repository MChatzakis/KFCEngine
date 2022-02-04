#include "Goomba.h"
#include "../engine/CollisionChecker.h"

//GOOMBAS
void Goomba::createSprite(Point p) {
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

void Goomba::createGoombaWalkAnimations() {
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

	deathAnimator = new MovingAnimator();
	deathAnimator->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const MovingAnimation*>(&anim));
			Sprite_MoveAction(this->sprite, (const MovingAnimation&)anim);
		}
	);

	deathAnimator->SetOnFinish(
		[this](Animator* animator) {
			die();
		}
	);

	deathAnimator->SetOnStart(
		[this](Animator* animator) {

		}
	);

	deathAnimation = new MovingAnimation(GOOMBA_DEATH_ID, 1, 4, 4, 500);
}

Goomba::Goomba(int _dx, int _dir, Point sp) {
	direction = _dir;
	dx = _dx;

	createSprite(sp);
	createGoombaWalkAnimations();
}

Goomba::Goomba(int _dx, int _dir, Point sp, int _del) {
	direction = _dir;
	dx = _dx;
	delay = _del;

	createSprite(sp);
	createGoombaWalkAnimations();
}

Goomba::Goomba(int _dx, int _dir, Point sp, int _del, int _ddel) {
	direction = _dir;
	dx = _dx;
	delay = _del;
	deathDelay = _ddel;

	createSprite(sp);
	createGoombaWalkAnimations();
}

Sprite* Goomba::getSprite() {
	return sprite;
}

void Goomba::setSprite(Sprite* s) {
	sprite = s;
}

int Goomba::getDx() {
	return dx;
}

void Goomba::setDx(int _dx) {
	dx = _dx;
}

int Goomba::getDirection() {
	return direction;
}

void Goomba::setDirection(int _dir) {
	direction = _dir;
	goombaWalkAnimation->SetDx(dx * direction);

	/*if (direction > 0) {
		sprite->SetStateId("running_right");
	}
	else {
		sprite->SetStateId("running_left");
	}*/
}

void Goomba::destroyAnimators() {
	//if (!goombaWalkAnimator->HasFinished()) {
	//goombaWalkAnimator->Stop();
	//}

	//if (!deathAnimator->HasFinished()) {
	//deathAnimator->Stop();
	//}
	goombaWalkAnimator->Destroy();
	deathAnimator->Destroy();
}

void Goomba::walk() {

	if ((!(goombaWalkAnimator->HasFinished()) || !deathAnimator->HasFinished() || !this->sprite->IsAlive()))
		return;

	goombaWalkAnimator->Start(goombaWalkAnimation, CurrTime());
}

//GOOMBA HOLDER

GoombaHolder GoombaHolder::holder;

auto GoombaHolder::GetSingleton(void) -> GoombaHolder& { return holder; }

auto GoombaHolder::GetSingletonConst(void) -> const GoombaHolder& { return holder; }

void GoombaHolder::CreateGoombaMap(nlohmann::json conf) {
	int dx = conf["dx"];
	int delay = conf["delay"];
	nlohmann::json entityArr = conf["goombas"];
	for (auto g : entityArr) {
		Goomba* gom = new Goomba(dx, g["direction"], Point{ g["x"], g["y"] }, delay);
		Sprite* s = gom->getSprite();

		Goombas[s] = gom;

		SpriteManager::GetSingleton().Add(s);
	}

}

void GoombaHolder::CreateGoombaMap(std::list<Point>point) {
	for (auto p : point) {
		Goomba* g = new Goomba(1, 1, p);
		Sprite* s = g->getSprite();

		Goombas[s] = g;

		SpriteManager::GetSingleton().Add(s);
	}
}

void GoombaHolder::ErasePair_freeGoomba(Sprite* s) {
	Goomba* gToDel = Goombas[s];
	Goombas.erase(s);
	//delete gToDel; //exception when enabled
}

void GoombaHolder::Initialize(std::list<Point>points) {
	//createGoombas(point);
	//createGoombaSprites();
	CreateGoombaMap(points);
}

void GoombaHolder::Initialize(nlohmann::json conf) {
	//createGoombas(point);
	//createGoombaSprites();
	CreateGoombaMap(conf);
}

std::list<Sprite*> GoombaHolder::GetGoombaSpritesList() {
	std::list<Sprite*>l;
	for (auto e : Goombas) {
		l.push_back(e.first);
	}
	return l;
}

std::list<Goomba*> GoombaHolder::GetGoombaClassList() {
	std::list<Goomba*>l;
	for (auto e : Goombas) {
		l.push_back(e.second);
	}
	return l;
}

std::map<Sprite*, Goomba*>& GoombaHolder::GetGoombaMap() {
	return Goombas;
}

void GoombaHolder::SetGoombaMap(std::map<Sprite*, Goomba*>gs) {
	Goombas = std::map<Sprite*, Goomba*>(gs);
}

void GoombaHolder::WalkGoombas() {
	for (auto g : Goombas) {
		g.second->walk();
	}
}

Goomba* GoombaHolder::GetInstanceOf(Sprite* s) {
	return Goombas[s];
}

void Goomba::stopAnimators() {
	if (!goombaWalkAnimator->HasFinished()) {
		goombaWalkAnimator->Stop();
	}

	if (!deathAnimator->HasFinished()) {
		deathAnimator->Stop();
	}
}

void Goomba::dieAction() {
	stopAnimators();
	
	sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GOOMBA_DEATH_ID), GOOMBA_DEATH_ID);
	//goombaWalkAnimator->Stop();
	
	deathAnimator->Start(deathAnimation, CurrTime());
}

void Goomba::die() {
	SpriteManager::GetSingleton().Remove(this->sprite);
	this->sprite->Destroy();
}

MovingAnimator* Goomba::getDeathAnimator() {
	return deathAnimator;
}

