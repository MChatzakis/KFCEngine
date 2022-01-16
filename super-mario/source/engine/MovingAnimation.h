#ifndef _MOVINGANIMATION_H_
#define _MOVINGANIMATION_H_

#include "./Animation.h"

class MovingAnimation : public Animation {
protected:
	unsigned reps = 1; // 0=forever
	int dx = 0, dy = 0;
	unsigned delay = 0;
public:
	using Me = MovingAnimation;
	int GetDx(void) const;
	Me& SetDx(int v);
	int GetDy(void) const;
	Me& SetDy(int v);
	unsigned GetDelay(void) const;
	Me& SetDelay(unsigned v);
	unsigned GetReps(void) const;
	Me& SetReps(unsigned n);
	bool IsForever(void) const;
	Me& SetForever(void);
	Animation* Clone(void) const override;
	MovingAnimation(const std::string& _id, unsigned _reps, int _dx, int _dy, unsigned _delay);
};

int
MovingAnimation::GetDx(void) const { return dx; }

MovingAnimation::Me&
MovingAnimation::SetDx(int v) { dx = v; return *this; }

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

#endif _MOVINGANIMATION_H_