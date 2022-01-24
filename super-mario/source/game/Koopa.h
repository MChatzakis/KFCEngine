#ifndef _KOOPA_H_
#define _KOOPA_H_

#define GREEN_KOOPA_WALK_RIGHT_ID "greenKoopa.walkRight"
#define GREEN_KOOPA_WALK_LEFT_ID "greenKoopa.walkLeft"
#define GREEN_KOOPA_SHELL_ID "greenKoopa.shell"
#define GREEN_KOOPA_DEATH_ID "greenKoopa.death"

class Koopa {
private:
    Sprite* sprite_walkingRight = nullptr;
	Sprite* sprite_walkingLeft = nullptr;
	Sprite* sprite_shell = nullptr;
	Sprite* sprite_death = nullptr;

	FrameRangeAnimator* animator_walkingRight = nullptr;

	static Koopa koopa;
public:
    Koopa() {

	}

	static auto GetSingleton(void) -> Koopa& { return koopa; }
	static auto GetSingletonConst(void) -> const Koopa& { return koopa; }

	void initializeSprites();
	void initializeAnimators();

	void initialize();

	void runRight();

	void displayKoopaWalkingRight_DEBUG(Bitmap target);

};

Koopa Koopa::koopa;

void Koopa::initializeSprites() {
	sprite_walkingRight = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_RIGHT_ID), GREEN_KOOPA_WALK_RIGHT_ID);
	sprite_walkingLeft = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_LEFT_ID), GREEN_KOOPA_WALK_LEFT_ID);

	sprite_walkingRight = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_RIGHT_ID), GREEN_KOOPA_WALK_RIGHT_ID);
	sprite_walkingRight->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), sprite_walkingRight));
	/*sprite_walkingRight->GetQuantizer().SetMover(
		[this](const Rect& r, int* dx, int* dy) {
			GridUtilities::FilterGridMotion(r, dx, dy);
		}
	);*/
	/*sprite_walkingRight->GetQuantizer().SetMover(
		[this](const Rect& r, int* dx, int* dy) {
		this->GetSingleton().sprite_walkingRight->SetPos(r.x + *dx, r.y + *dy);
			//r.x += *dx;
			//r.y += *dy;
			
		}
	);*/
	
	sprite_walkingLeft = new Sprite(10, 380, (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(GREEN_KOOPA_WALK_LEFT_ID), GREEN_KOOPA_WALK_LEFT_ID);

	SpriteManager::GetSingleton().Add(sprite_walkingRight);
	SpriteManager::GetSingleton().Add(sprite_walkingLeft);
    SpriteManager::GetSingleton().Add(sprite_shell);
	SpriteManager::GetSingleton().Add(sprite_death);
}

void Koopa::initializeAnimators() {
	animator_walkingRight = new FrameRangeAnimator();
	

	animator_walkingRight->SetOnAction(
		[this](Animator* animator, const Animation& anim) {
			FrameRange_Action(this->sprite_walkingRight, animator, (const FrameRangeAnimation&)anim);
		}
	);

	animator_walkingRight->SetOnFinish(
		[this](Animator* animator) {
			AnimatorManager::GetSingleton().MarkAsSuspended(animator_walkingRight);
		}
	);

	AnimatorManager::GetSingleton().Register(animator_walkingRight);
}

void Koopa::initialize() {
	initializeSprites();
	initializeAnimators();
}

void Koopa::runRight() {
	animator_walkingRight->Start(new FrameRangeAnimation(GREEN_KOOPA_WALK_RIGHT_ID, 0, 2, 3, 3, 0, 70), CurrTime());
	AnimatorManager::GetSingleton().MarkAsRunning(animator_walkingRight);
	//animator_walkingRight->setAnimation(GREEN_KOOPA_WALK_RIGHT_ID, 0, 2, 1, 3, 0, 15);
}

void Koopa::displayKoopaWalkingRight_DEBUG(Bitmap target) {
	sprite_walkingRight->Display(target);
}

#endif _KOOPA_H_