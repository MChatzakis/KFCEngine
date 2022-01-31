#include "./Mario.h"

Mario Mario::mario;
auto Mario::GetSingleton(void) -> Mario& { return mario; }
auto Mario::GetSingletonConst(void) -> const Mario& { return mario; }

Sprite* Mario::GetCurrSprite() {
	return currSprite;
}

void Mario::backToIdle() {
	if (MARIO_IDLE || MARIO_FALLING || MARIO_JUMPING)/*) || MARIO_FALLING || -> if we add that it jumps always in the same way*/
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

	currSprite = new Sprite(conf["startingPosition"]["x"], conf["startingPosition"]["y"], (AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_IDLE_RIGHT_ID), MARIO_IDLE_RIGHT_ID);
	currSprite->SetStateId("falling_right");

	currSprite->SetMover(MakeSpriteGridLayerMover(gameMap->GetGrid(), currSprite));

	PrepareSpriteGravityHandler(gameMap->GetGrid(), currSprite);

	currSprite->GetGravityHandler().SetOnStartFalling(
		[this]()
	{
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
		else if (id == "falling_left") {
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

	AddAnimation("moving_right", new FrameRangeAnimation(MARIO_WALK_RIGHT_ID, 0, conf["moving"]["frames"], conf["moving"]["repetitions"], 0, 0, 0)); //set dx, dy, delay on functions
	AddAnimation("moving_left", new FrameRangeAnimation(MARIO_WALK_LEFT_ID, 0, conf["moving"]["frames"], conf["moving"]["repetitions"], 0, 0, 0));

	AddAnimation("vertical_jumping_right", new MovingAnimation(MARIO_JUMP_RIGHT_ID, conf["jumping"]["repetitions"], 0, 0, 0));
	AddAnimation("vertical_jumping_left", new MovingAnimation(MARIO_JUMP_LEFT_ID, conf["jumping"]["repetitions"], 0, 0, 0));

	AddAnimation("parabola_jumping_right", new FrameRangeAnimation(MARIO_JUMP_RIGHT_ID, 0, 0, conf["verticalJumping"]["repetitions"], 0, 0, 0));
	AddAnimation("parabola_jumping_left", new FrameRangeAnimation(MARIO_JUMP_LEFT_ID, 0, 0, conf["verticalJumping"]["repetitions"], 0, 0, 0));
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
		else {
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

void Mario::initialize(nlohmann::json _c) {
	conf = _c;

	initializeAnimations();
	initializeSprites();
	initializeAnimators();

	totalLifes = conf["totalLifes"];
}

void Mario::runRight() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_RIGHT_ID && */ currSprite->GetStateId() == "running_right"))
		return;

	currSprite->SetStateId("running_right");
	FrameRangeAnimator* running = (FrameRangeAnimator*)GetAnimator("running");

	StopAnimators();

	FrameRangeAnimation* runningRight = (FrameRangeAnimation*)GetAnimation("moving_right");
	runningRight->SetDx(conf["moving"]["dx"]);
	runningRight->SetDelay(conf["moving"]["delay"]);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);

	running->Start(runningRight, CurrTime());
}

void Mario::walkRight() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_RIGHT_ID && */ currSprite->GetStateId() == "walking_right"))
		return;

	currSprite->SetStateId("walking_right");
	FrameRangeAnimator* running = (FrameRangeAnimator*)GetAnimator("running");

	StopAnimators();

	FrameRangeAnimation* walkingRight = (FrameRangeAnimation*)GetAnimation("moving_right");
	walkingRight->SetDx(conf["walking"]["dx"]);
	walkingRight->SetDelay(conf["walking"]["delay"]);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_RIGHT_ID), MARIO_WALK_RIGHT_ID);

	running->Start(walkingRight, CurrTime());
}

void Mario::walkLeft() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_LEFT_ID &&*/ currSprite->GetStateId() == "walking_left"))
		return;

	currSprite->SetStateId("walking_left");
	FrameRangeAnimator* running = (FrameRangeAnimator*)GetAnimator("running");

	StopAnimators();

	FrameRangeAnimation* walkingLeft = (FrameRangeAnimation*)GetAnimation("moving_left");
	walkingLeft->SetDx(-1 * conf["walking"]["dx"]);
	walkingLeft->SetDelay(conf["walking"]["delay"]);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);

	running->Start(walkingLeft, CurrTime());
}

void Mario::runLeft() {
	if (MARIO_JUMPING || MARIO_FALLING || (!(GetAnimator("running")->HasFinished()) && /*currSprite->GetAnimationFilm()->GetId() == MARIO_WALK_LEFT_ID &&*/ currSprite->GetStateId() == "running_left"))
		return;

	currSprite->SetStateId("running_left");
	FrameRangeAnimator* running = (FrameRangeAnimator*)GetAnimator("running");

	StopAnimators();

	FrameRangeAnimation* runningLeft = (FrameRangeAnimation*)GetAnimation("moving_left");
	runningLeft->SetDx(-1 * conf["moving"]["dx"]);
	runningLeft->SetDelay(conf["moving"]["delay"]);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_WALK_LEFT_ID), MARIO_WALK_LEFT_ID);

	running->Start(runningLeft, CurrTime());
}

void Mario::jumpVerticalLeft() {
	currSprite->SetStateId("jumping_vertical_left");

	MovingAnimator* jumping = (MovingAnimator*)GetAnimator("jumping");
	MovingAnimation* jumpingLeft = (MovingAnimation*)GetAnimation("vertical_jumping_left");
	jumpingLeft->SetDy(-1 * conf["verticalJumping"]["dy"]);
	jumpingLeft->SetDelay(conf["verticalJumping"]["delay"]);
	jumpingLeft->SetReps(conf["verticalJumping"]["repetitions"]);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_LEFT_ID), MARIO_JUMP_LEFT_ID);

	jumping->Start(jumpingLeft, CurrTime());
}

void Mario::jumpVerticalRight() {
	currSprite->SetStateId("jumping_vertical_right");

	MovingAnimator* jumping = (MovingAnimator*)GetAnimator("jumping");
	MovingAnimation* jumpingRight = (MovingAnimation*)GetAnimation("vertical_jumping_right");
	jumpingRight->SetDy(-1 * conf["verticalJumping"]["dy"]);
	jumpingRight->SetDelay(conf["verticalJumping"]["delay"]);
	jumpingRight->SetReps(conf["verticalJumping"]["repetitions"]);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);

	jumping->Start(jumpingRight, CurrTime());
}

void Mario::jumpRight() {
	currSprite->SetStateId("jumping_right");

	FrameRangeAnimator* parabola_jumping = (FrameRangeAnimator*)GetAnimator("parabola_jumping");
	FrameRangeAnimation* parabola_jumpingRight = (FrameRangeAnimation*)GetAnimation("parabola_jumping_right");
	parabola_jumpingRight->SetDx(conf["jumping"]["dx"]);
	parabola_jumpingRight->SetDy(-1 * conf["jumping"]["dy"]);
	parabola_jumpingRight->SetDelay(conf["jumping"]["delay"]);
	parabola_jumpingRight->SetReps(conf["jumping"]["repetitions"]); // 8 * 8 + 1

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);

	parabola_jumping->Start(parabola_jumpingRight, CurrTime());
}

void Mario::jumpLeft() {
	currSprite->SetStateId("jumping_left");

	FrameRangeAnimator* jumping = (FrameRangeAnimator*)GetAnimator("parabola_jumping");
	FrameRangeAnimation* parabola_jumpingLeft = (FrameRangeAnimation*)GetAnimation("parabola_jumping_left");
	parabola_jumpingLeft->SetDx(-1 * conf["jumping"]["dx"]);
	parabola_jumpingLeft->SetDy(-1 * conf["jumping"]["dy"]);
	parabola_jumpingLeft->SetDelay(conf["jumping"]["delay"]);
	parabola_jumpingLeft->SetReps(conf["jumping"]["repetitions"]); // 8 * 8 + 1

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
	else if (spriteStateId == "walking_right" || spriteStateId == "running_right") {
		jumpRight();
	}
	else { //else if spriteStateId == "walking_left" || spriteStateId == "running_left"
		jumpLeft();
	}
}

//for enemy kill animation
void Mario::smallJump() { //bounce

	std::string spriteStateId = currSprite->GetStateId();
	StopAnimators();

	if (spriteStateId == "idle_right") {
		smallJumpVerticalRight();
	}
	else if (spriteStateId == "idle_left") {
		smallJumpVerticalLeft();
	}
	else if (MARIO_MOVING_RIGHT) {
		smallJumpRight();
	}
	else {
		smallJumpLeft();
	}
}

//ok
void Mario::smallJumpVerticalLeft() {
	currSprite->SetStateId("jumping_vertical_left");

	MovingAnimator* jumping = (MovingAnimator*)GetAnimator("jumping");
	MovingAnimation* jumpingLeft = (MovingAnimation*)GetAnimation("vertical_jumping_left");
	/*jumpingLeft->SetDy(-1 * conf["running"]["dx"]);
	jumpingLeft->SetDelay(conf["running"]["delay"]);*/
	jumpingLeft->SetDy(-1 * conf["smallVerticalJumping"]["dy"]);
	jumpingLeft->SetDelay(conf["smallVerticalJumping"]["delay"]);
	jumpingLeft->SetReps(conf["smallVerticalJumping"]["repetitions"]);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_LEFT_ID), MARIO_JUMP_LEFT_ID);

	jumping->Start(jumpingLeft, CurrTime());
}

//ok
void Mario::smallJumpVerticalRight() {
	currSprite->SetStateId("jumping_vertical_right");

	MovingAnimator* jumping = (MovingAnimator*)GetAnimator("jumping");
	MovingAnimation* jumpingRight = (MovingAnimation*)GetAnimation("vertical_jumping_right");
	jumpingRight->SetDy(-1 * conf["smallVerticalJumping"]["dy"]);
	jumpingRight->SetDelay(conf["smallVerticalJumping"]["delay"]);
	jumpingRight->SetReps(conf["smallVerticalJumping"]["repetitions"]);

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);

	jumping->Start(jumpingRight, CurrTime());
}

//ok
void Mario::smallJumpVertical() {
	std::string spriteStateId = currSprite->GetStateId();
	if (MARIO_JUMPING)//|| */currSprite->GetGravityHandler().IsFalling())
		return;

	//std::string id = currSprite->GetAnimationFilm()->GetId();
	StopAnimators();

	if (spriteStateId == "running_right" || spriteStateId == "walking_right" || spriteStateId == "idle_right") {
		smallJumpVerticalRight();
	}
	else /*if (id == MARIO_IDLE_LEFT_ID || id == MARIO_WALK_LEFT_ID)*/ {
		smallJumpVerticalLeft();
	}
}

//ok
void Mario::smallJumpRight() {
	currSprite->SetStateId("jumping_right");

	FrameRangeAnimator* parabola_jumping = (FrameRangeAnimator*)GetAnimator("parabola_jumping");
	FrameRangeAnimation* parabola_jumpingRight = (FrameRangeAnimation*)GetAnimation("parabola_jumping_right");
	parabola_jumpingRight->SetDx(conf["smallJumping"]["dx"]);
	parabola_jumpingRight->SetDy(-1 * conf["smallJumping"]["dy"]);
	parabola_jumpingRight->SetDelay(conf["smallJumping"]["delay"]);
	parabola_jumpingRight->SetReps(conf["smallJumping"]["repetitions"]); // 8 * 8 + 1

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_RIGHT_ID), MARIO_JUMP_RIGHT_ID);

	parabola_jumping->Start(parabola_jumpingRight, CurrTime());
}

//ok
void Mario::smallJumpLeft() {
	currSprite->SetStateId("jumping_left");

	FrameRangeAnimator* jumping = (FrameRangeAnimator*)GetAnimator("parabola_jumping");
	FrameRangeAnimation* parabola_jumpingLeft = (FrameRangeAnimation*)GetAnimation("parabola_jumping_left");
	parabola_jumpingLeft->SetDx(-1 * conf["smallJumping"]["dx"]);
	parabola_jumpingLeft->SetDy(-1 * conf["smallJumping"]["dy"]);
	parabola_jumpingLeft->SetDelay(conf["smallJumping"]["delay"]);
	parabola_jumpingLeft->SetReps(conf["smallJumping"]["repetitions"]); // 8 * 8 + 1

	currSprite->ChangeAnimationFilm((AnimationFilm*)AnimationFilmHolder::GetSingleton().GetFilm(MARIO_JUMP_LEFT_ID), MARIO_JUMP_LEFT_ID);

	jumping->Start(parabola_jumpingLeft, CurrTime());
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

	GAME_HAS_ENDED = 1;
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

void Mario::setScore(int _s) {
	score = _s;
}

int Mario::getScore() {
	return score;
}

void Mario::setTotalLifes(int _tl) {
	totalLifes = _tl;
}

int Mario::getTotalLifes() {
	return totalLifes;
}

void Mario::setCoins(int _c) {
	totalCoins = _c;
}

int Mario::getCoins() {
	return totalCoins;
}

void Mario::increaseScoreBy(int by) {
	score += by;
}

void Mario::increaseCoinsBy(int by) {
	totalCoins += by;
}

void Mario::decreaseLifes() {
	totalLifes--;
}

void Mario::Respawn() {
	currSprite->SetPos(conf["startingPosition"]["x"], conf["startingPosition"]["y"]);
	currSprite->Move(1, 0);
	gameMap->SetViewWindow(Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)); //bad
}

void Mario::EvaluateDeathAction() {
	decreaseLifes();

	if (totalLifes == 0) {
		Die();
	}
	else {
		Respawn();
	}
}