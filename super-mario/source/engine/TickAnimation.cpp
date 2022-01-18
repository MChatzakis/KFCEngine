#include "./TickAnimation.h"

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
TickAnimation::Clone(void) const //override
{
	//isDiscrete = true;
	return new TickAnimation(id, delay, reps, /*isDiscrete = true*/true);
}

TickAnimation::TickAnimation(const std::string& _id, unsigned d, unsigned r, bool discrete) :
	Animation(id), delay(d), reps(r), isDiscrete(discrete) {
	assert(Inv());
}