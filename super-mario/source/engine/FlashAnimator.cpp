#include "./FlashAnimator.h"


auto
FlashAnimator::GetAnim(void) const -> const FlashAnimation&
{
	return *anim;
}
void
FlashAnimator::Start(FlashAnimation* a, timestamp_t t) {
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	currRep = 0; //?
	NotifyStarted();
}

void
FlashAnimator::Progress(timestamp_t currTime) {
	while (currTime > lastTime && (currTime - lastTime) >= anim->GetShowDelay()) {
		lastTime += anim->GetShowDelay();
		NotifyAction(*anim);
		if (/*!anim->IsForever() && */++currRep == anim->GetRepetitions()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
	}
}

/*void Sprite_MoveAction(Sprite* sprite, const FlashAnimation& anim) {
	sprite->Move(anim.GetDx(), anim.GetDy());
}*/