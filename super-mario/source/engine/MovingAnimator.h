#ifndef _MOVINGANIMATOR_H_
#define _MOVINGANIMATOR_H_

#include <iostream>
#include <set>

#include "./Animator.h"
#include "./MovingAnimation.h"


class MovingAnimator : public Animator {
protected:
	MovingAnimation* anim = nullptr;
	unsigned currRep = 0; // animation state
public:
	void Progress(timestamp_t currTime);
	auto GetAnim(void) const -> const MovingAnimation&;
	void Start(MovingAnimation* a, timestamp_t t);
	MovingAnimator(void) = default;
};


#endif _MOVINGANIMATOR_H_