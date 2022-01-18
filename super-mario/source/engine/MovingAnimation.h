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

#endif _MOVINGANIMATION_H_