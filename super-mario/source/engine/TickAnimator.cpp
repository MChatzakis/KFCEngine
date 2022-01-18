#include "./TickAnimator.h"

unsigned
TickAnimator::GetCurrRep(void) const { return currRep; }

unsigned
TickAnimator::GetElapsedTime(void) const { return elapsedTime; }

float
TickAnimator::GetElapsedTimeNormalised(void) const
{
	return float(elapsedTime) / float(anim->GetDelay());
}

void
TickAnimator::Start(const TickAnimation& a, timestamp_t t) {
	anim = (TickAnimation*)a.Clone();
	lastTime = t;
	state = ANIMATOR_RUNNING;
	currRep = 0;
	elapsedTime = 0;
	NotifyStarted();
}