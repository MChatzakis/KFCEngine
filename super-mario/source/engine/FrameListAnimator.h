#ifndef _FRAMELISTANIMATOR_H_
#define _FRAMELISTANIMATOR_H_

#include "./FrameListAnimation.h"
#include "./Sprite.h"

#include "./Animator.h"

class FrameListAnimator : public Animator {
protected:
	FrameListAnimation* anim = nullptr;
	unsigned currFrame = 0; // animation state
	unsigned currRep = 0; // animation state
public:
	void Progress(timestamp_t currTime);
	unsigned GetCurrFrame(void) const;
	unsigned GetCurrRep(void) const;
	void Start(FrameListAnimation* a, timestamp_t t);
	FrameListAnimator(void) = default;

	void setAnimation(const std::string& _id, unsigned s, unsigned e, unsigned r, int dx, int dy, int d);
};

void FrameList_Action(Sprite* sprite, Animator* animator, const FrameListAnimation& anim);
void FrameList_Action_DecreasingDY(Sprite* sprite, Animator* animator, const FrameListAnimation& anim);

#endif _FRAMELISTANIMATOR_H_