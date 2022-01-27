#ifndef _MOVINGPATHANIMATOR_H_
#define _MOVINGPATHANIMATOR_H_

#include "./Animator.h"
#include "./MovingPathAnimation.h"

class MovingPathAnimator : public Animator {
protected:
	MovingPathAnimation* anim = nullptr;
	unsigned currRep = 0; // animation state

public:
	void Progress(timestamp_t currTime);
	void setAnimation(const std::string& _id, unsigned s, unsigned e, unsigned r, int dx, int dy, int d);
	void Start(MovingPathAnimation* a, timestamp_t t);
	MovingPathAnimator(void) = default;

};

void MovingPath_Action(Sprite* sprite, Animator* animator, const MovingPathAnimation& anim);


#endif _MOVINGPATHANIMATOR_H_