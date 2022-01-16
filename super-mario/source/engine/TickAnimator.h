#ifndef _TICKANIMATOR_H_
#define _TICKANIMATOR_H_

#include <iostream>
#include <set>

#include "./Animator.h"
#include "./TickAnimation.h"


class TickAnimator : public Animator {
protected:
	TickAnimation* anim = nullptr;
	unsigned currRep = 0;
	unsigned elapsedTime = 0; // keep track of time passed between triggers
public:
	void Progress(timestamp_t currTime) override;
	unsigned GetCurrRep(void) const;
	unsigned GetElapsedTime(void) const;
	float GetElapsedTimeNormalised(void) const;
	void Start(const TickAnimation& a, timestamp_t t);
	TickAnimator(void) = default;
};

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

#endif _TICKANIMATOR_H_

