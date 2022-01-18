#include "./FrameRangeAnimation.h"

unsigned
FrameRangeAnimation::GetStartFrame(void) const { return start; }

FrameRangeAnimation::Me&
FrameRangeAnimation::SetStartFrame(unsigned v) { start = v; return *this; }

unsigned
FrameRangeAnimation::GetEndFrame(void) const { return end; }

FrameRangeAnimation::Me&
FrameRangeAnimation::SetEndFrame(unsigned v) { end = v; return *this; }

Animation*
FrameRangeAnimation::Clone(void) const //override
{
	return new FrameRangeAnimation(
		id, start, end, GetReps(), GetDx(), GetDy(), GetDelay()
	);
}

FrameRangeAnimation::FrameRangeAnimation(
	const std::string& _id,
	unsigned s, unsigned e,
	unsigned r, int dx, int dy, int d
) : start(s), end(e), MovingAnimation(id, r, dx, dy, d) {}