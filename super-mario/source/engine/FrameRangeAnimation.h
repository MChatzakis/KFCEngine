#ifndef _FRAMERANGEANIMATION_H_
#define _FRAMERANGEANIMATION_H_

#include "./MovingAnimation.h"

class FrameRangeAnimation : public MovingAnimation {
protected:
	unsigned start = 0, end = 0;
public:
	using Me = FrameRangeAnimation;
	unsigned GetStartFrame(void) const { return start; }
	Me& SetStartFrame(unsigned v) { start = v; return *this; }
	unsigned GetEndFrame(void) const { return end; }
	Me& SetEndFrame(unsigned v) { end = v; return *this; }
	Animation* Clone(void) const override {
		return new FrameRangeAnimation(
			id, start, end, GetReps(), GetDx(), GetDy(), GetDelay()
		);
	}
	FrameRangeAnimation(
		const std::string& _id,
		unsigned s, unsigned e,
		unsigned r, int dx, int dy, int d
	) : start(s), end(e), MovingAnimation(id, r, dx, dy, d) {}

};

#endif _FRAMERANGEANIMATION_H_