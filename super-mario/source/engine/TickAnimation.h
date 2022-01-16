#ifndef _TICKANIMATION_H_
#define _TICKANIMATION_H_

#include "./Animation.h"

class TickAnimation : public Animation {
protected:
	unsigned delay = 0;
	unsigned reps = 1;
	bool isDiscrete = true; // false: when used for custom timed actions
	bool Inv(void) const;
public:
	using Me = TickAnimation;
	unsigned GetDelay(void) const;
	Me& SetDelay(unsigned v);
	unsigned GetReps(void) const;
	Me& SetReps(unsigned n);
	bool IsForever(void) const;
	Me& SetForever(void);
	bool IsDiscrete(void) const;
	Animation* Clone(void) const override;
	TickAnimation(const std::string& _id, unsigned d, unsigned r, bool discrete);
};

bool
TickAnimation::Inv(void) const { return isDiscrete || reps == 1; };

unsigned
TickAnimation::GetDelay(void) const { return delay; }

TickAnimation::Me&
TickAnimation::SetDelay(unsigned v) { delay = v; return *this; }

unsigned
TickAnimation::GetReps(void) const { return reps; }

TickAnimation::Me&
TickAnimation::SetReps(unsigned n) { reps = n; return *this; }

bool
TickAnimation::IsForever(void) const { return !reps; }

TickAnimation::Me&
TickAnimation::SetForever(void) { reps = 0; return *this; }

bool
TickAnimation::IsDiscrete(void) const { return isDiscrete; }

Animation*
TickAnimation::Clone(void) const override
{
	//isDiscrete = true;
	return new TickAnimation(id, delay, reps, /*isDiscrete = true*/true);
}

TickAnimation::TickAnimation(const std::string& _id, unsigned d, unsigned r, bool discrete) :
	Animation(id), delay(d), reps(r), isDiscrete(discrete) {
	assert(Inv());
}

#endif _TICKANIMATION_H_