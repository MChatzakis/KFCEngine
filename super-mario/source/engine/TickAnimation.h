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

#endif _TICKANIMATION_H_