#include "./MovingAnimation.h"

int MovingAnimation::GetDx(void) const { return dx; }

MovingAnimation::Me& MovingAnimation::SetDx(int v) { dx = v; return *this; }

int
MovingAnimation::GetDy(void) const { return dy; }

MovingAnimation::Me&
MovingAnimation::SetDy(int v) { dy = v; return *this; }

unsigned
MovingAnimation::GetDelay(void) const { return delay; }

MovingAnimation::Me&
MovingAnimation::SetDelay(unsigned v) { delay = v; return *this; }

unsigned
MovingAnimation::GetReps(void) const { return reps; }

MovingAnimation::Me&
MovingAnimation::SetReps(unsigned n) { reps = n; return *this; }

bool
MovingAnimation::IsForever(void) const { return !reps; }

MovingAnimation::Me&
MovingAnimation::SetForever(void) { reps = 0; return *this; }

Animation*
MovingAnimation::Clone(void) const //override
{
	return new MovingAnimation(id, reps, dx, dy, delay);
}

MovingAnimation::MovingAnimation(
	const std::string& _id, unsigned _reps, int _dx, int _dy, unsigned _delay
) : Animation(_id), reps(_reps), dx(_dx), dy(_dy), delay(_delay) {}