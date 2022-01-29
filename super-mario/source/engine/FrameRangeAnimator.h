#ifndef _FRAMERANGEANIMATOR_H_
#define _FRAMERANGEANIMATOR_H_

#include "./FrameRangeAnimation.h"
#include "./Sprite.h"

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

	void setAnimation(const std::string& _id, unsigned s, unsigned e, unsigned r, int dx, int dy, int d);
};

void FrameRange_Action(Sprite* sprite, Animator* animator, const FrameRangeAnimation& anim);
void FrameRange_Action_DecreasingDY(Sprite* sprite, Animator* animator, const FrameRangeAnimation& anim);

#endif _FRAMERANGEANIMATOR_H_