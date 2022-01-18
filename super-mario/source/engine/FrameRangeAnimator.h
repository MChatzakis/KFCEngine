#ifndef _FRAMERANGEANIMATOR_H_
#define _FRAMERANGEANIMATOR_H_

#include "./FrameRangeAnimation.h"

#include "./Animator.h"

class FrameRangeAnimator : public Animator {
protected:
	FrameRangeAnimation* anim = nullptr;
	unsigned currFrame = 0; // animation state
	unsigned currRep = 0; // animation state
public:
	void Progress(timestamp_t currTime);
	unsigned GetCurrFrame(void) const;
	unsigned GetCurrRep(void) const;
	void Start(FrameRangeAnimation* a, timestamp_t t);
	FrameRangeAnimator(void) = default;
};

#endif _FRAMERANGEANIMATOR_H_