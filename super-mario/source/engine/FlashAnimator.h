#ifndef _FLASHANIMATOR_H_
#define _FLASHANIMATOR_H_

#include <iostream>
#include <set>

#include "./Animator.h"
#include "./FlashAnimation.h"
#include "./Sprite.h"


class FlashAnimator : public Animator {
protected:
	FlashAnimation* anim = nullptr;
	unsigned currRep = 0; // animation state
public:
	void Progress(timestamp_t currTime);
	auto GetAnim(void) const -> const FlashAnimation&;
	void Start(FlashAnimation* a, timestamp_t t);
	FlashAnimator(void) = default;

	
};

//void Sprite_MoveAction(Sprite* sprite, const FlashAnimation& anim); 

#endif _FLASHANIMATOR_H_