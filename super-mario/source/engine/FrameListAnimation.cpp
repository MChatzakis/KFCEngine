#include "./FrameListAnimation.h"

const FrameListAnimation::Frames&
FrameListAnimation::GetFrames(void) const
{
	return frames;
}

void
FrameListAnimation::SetFrames(const Frames& f)
{
	frames = f;
}

Animation*
FrameListAnimation::Clone(void) const //override
{
	return new FrameListAnimation(id, frames, GetReps(), GetDx(), GetDy(), GetDelay(), false); //it wants a boolean value
}

FrameListAnimation::FrameListAnimation(
	const std::string& _id,
	const Frames& _frames,
	unsigned r, int dx, int dy, unsigned d, bool c
) : frames(_frames), MovingAnimation(id, r, dx, dy, d) {}