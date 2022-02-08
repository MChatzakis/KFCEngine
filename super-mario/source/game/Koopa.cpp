#include "Koopa.h"

//KOOPAS
void Koopa::createSprite(Point p) {
	if (direction > 0) {
		sprite = new Sprite(p.x, p.y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_RIGHT_ID), GREEN_KOOPA_WALK_RIGHT_ID);
	}
	else {
		sprite = new Sprite(p.x, p.y, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_LEFT_ID), GREEN_KOOPA_WALK_LEFT_ID);
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
}

void Koopa::createKoopaWalkAnimations() {
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

void Koopa::createKoopaShellAnimations() {
	greenKoopaShellAnimator = new MovingAnimator();
	greenKoopaShellAnimator->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			assert(dynamic_cast<const MovingAnimation*>(&anim));
			Sprite_MoveAction(this->sprite, (const MovingAnimation&)anim);
		}
	);

	greenKoopaShellAnimator->SetOnFinish(
		[this](Animator* animator) {

		}
	);

	greenKoopaShellAnimator->SetOnStart(
		[this](Animator* animator) {

		}
	);

	greenKoopaShellAnimation = new MovingAnimation(GREEN_KOOPA_SHELL_ID, 1, 0, 0, shellDelay);
}

Koopa::Koopa(int _dx, int _dir, Point sp) {
	direction = _dir;
	dx = _dx;

	createSprite(sp);
	createKoopaWalkAnimations();
	createKoopaShellAnimations();
}

Koopa::Koopa(int _dx, int _dir, Point sp, int _del) {
	direction = _dir;
	dx = _dx;
	delay = _del;

	createSprite(sp);
	createKoopaWalkAnimations();
	createKoopaShellAnimations();

}

Koopa::Koopa(int _dx, int _dir, Point sp, int _del, int _sdx, int _sdl) {
	direction = _dir;
	dx = _dx;
	delay = _del;
	shellDelay = _sdl;
	shellDx = _sdx;

	createSprite(sp);
	createKoopaWalkAnimations();
	createKoopaShellAnimations();
}

Sprite* Koopa::getSprite() {
	return sprite;
}

void Koopa::setSprite(Sprite* s) {
	sprite = s;
}

int Koopa::getDx() {
	return dx;
}

void Koopa::setDx(int _dx) {
	dx = _dx;
}

int Koopa::getDirection() {
	return direction;
}

void Koopa::setDirection(int _dir) {
	//direction = _dir;

	direction = _dir;
	koopaWalkAnimation->SetDx(dx * direction);

	if (state == SHELL) {
		return;
	}

	if (direction > 0) {
		//sprite->SetStateId("running_right");
		sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_RIGHT_ID), GREEN_KOOPA_WALK_RIGHT_ID);

	}
	else {
		//sprite->SetStateId("running_left");
		sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_LEFT_ID), GREEN_KOOPA_WALK_LEFT_ID);

	}

}

void Koopa::changeDirection() {

	direction *= -1;

	if (direction > 0) {
		//sprite->SetStateId("running_right");
		sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_RIGHT_ID), GREEN_KOOPA_WALK_RIGHT_ID);
	}
	else {
		//sprite->SetStateId("running_left");
		sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_LEFT_ID), GREEN_KOOPA_WALK_LEFT_ID);
	}

	koopaWalkAnimation->SetDx(dx * direction);

}

void Koopa::walk() {

	if (state == SHELL) {
		if ((!(greenKoopaShellAnimator->HasFinished())))
			return;
		
		if (isAtShellStartingState) {
			return;
		}

		greenKoopaShellAnimation->SetDx(direction * shellDx);
		greenKoopaShellAnimator->Start(greenKoopaShellAnimation, CurrTime());

		return;
	}
	else {
		if ((!(koopaWalkAnimator->HasFinished())))
			return;

		koopaWalkAnimator->Start(koopaWalkAnimation, CurrTime());
	}
	
}

void Koopa::setState(KoopaState _s) {
	state = _s;
}

KoopaState Koopa::getState() {
	return state;
}

void Koopa::stopAnimators() {
	if (!greenKoopaShellAnimator->HasFinished()) {
		greenKoopaShellAnimator->Stop();
	}

	if (!koopaWalkAnimator->HasFinished()) {
		koopaWalkAnimator->Stop();
	}
}

void Koopa::transformToShell() {
	state = SHELL;
	isAtShellStartingState = true;

	stopAnimators();
	sprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_SHELL_ID), GREEN_KOOPA_SHELL_ID);
	
	//greenKoopaShellAnimator->Start(greenKoopaShellAnimation, CurrTime());
}

void Koopa::evaluateStartingShellAction(int x) {
	if (x >= sprite->GetPosition().x) {
		direction = -1;
	}
	else {
		direction = 1;
	}

	isAtShellStartingState = false;
}

bool Koopa::getIsAtShellStartingState() {
	return isAtShellStartingState;
}

void Koopa::destroyAnimators() {
	greenKoopaShellAnimator->Destroy();
	koopaWalkAnimator->Destroy();
}

void Koopa::die() {
	SpriteManager::GetSingleton().Remove(this->sprite);
	this->destroyAnimators();
	this->sprite->Destroy();
}


//KOOPA HOLDER

KoopaHolder KoopaHolder::holder;
auto KoopaHolder::GetSingleton(void) -> KoopaHolder& { return holder; }
auto KoopaHolder::GetSingletonConst(void) -> const KoopaHolder& { return holder; }

void KoopaHolder::CreateKoopasMap(nlohmann::json conf) {
	int dx = conf["dx"];
	int delay = conf["delay"];
	int shellDx = conf["shellDx"];
	int shellDelay = conf["shellDelay"];
	nlohmann::json entityArr = conf["koopas"];
	for (auto g : entityArr) {
		Koopa* gom = new Koopa(dx, g["direction"], Point{ g["x"], g["y"] }, delay, shellDx, shellDelay);
		Sprite* s = gom->getSprite();

		Koopas[s] = gom;

		SpriteManager::GetSingleton().Add(s);
	}

}

void KoopaHolder::CreateKoopasMap(std::list<Point>point) {
	for (auto p : point) {
		Koopa* k = new Koopa(1, -1, p);
		Sprite* s = k->getSprite();

		Koopas[s] = k;
		SpriteManager::GetSingleton().Add(s);
	}
}

void KoopaHolder::Initialize(std::list<Point>point) {
	CreateKoopasMap(point);
}

void KoopaHolder::Initialize(nlohmann::json conf) {
	CreateKoopasMap(conf);
}


void KoopaHolder::ErasePair(Sprite* s) {
	Koopas.erase(s);
}

std::map<Sprite*, Koopa*>& KoopaHolder::GetKoopaMap() {
	return Koopas;
}

void KoopaHolder::setKoopaMap(std::map<Sprite*, Koopa*>m) {
	Koopas = std::map<Sprite*, Koopa*>(m);
}

std::list<Sprite*> KoopaHolder::GetKoopaSpritesList() {
	std::list<Sprite*>l;
	for (auto e : Koopas) {
		l.push_back(e.first);
	}
	return l;
}

std::list<Koopa*> KoopaHolder::GetKoopaClassList() {
	std::list<Koopa*>l;
	for (auto e : Koopas) {
		l.push_back(e.second);
	}
	return l;
}

void KoopaHolder::WalkKoopas() {
	for (auto g : Koopas) {
		g.second->walk();
	}
}

Koopa* KoopaHolder::GetInstanceOf(Sprite* s) {
	auto i = Koopas.find(s);
	return i != Koopas.end() ? i->second : nullptr;
}