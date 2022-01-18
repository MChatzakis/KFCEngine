#ifndef _FRAMERANGEANIMATION_H_
#define _FRAMERANGEANIMATION_H_

#include "./MovingAnimation.h"

class FrameRangeAnimation : public MovingAnimation {
protected:
	unsigned start = 0, end = 0;
public:
	using Me = FrameRangeAnimation;
	unsigned GetStartFrame(void) const;
	Me& SetStartFrame(unsigned v);
	unsigned GetEndFrame(void) const;
	Me& SetEndFrame(unsigned v);
	Animation* Clone(void) const override;
	FrameRangeAnimation(const std::string& _id,unsigned s, unsigned e,unsigned r, int dx, int dy, int d);
};

#endif _FRAMERANGEANIMATION_H_