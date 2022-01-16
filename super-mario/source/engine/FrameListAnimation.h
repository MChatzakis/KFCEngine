#ifndef _FRAMELISTANIMATION_H_
#define _FRAMELISTANIMATION_H_

#include <iostream>
#include <vector>

#include "MovingAnimation.h"

class FrameListAnimation : public MovingAnimation {
public:
	using Frames = std::vector<unsigned>;
protected:
	Frames frames;
public:
	const Frames& GetFrames(void) const;
	void SetFrames(const Frames& f);
	Animation* Clone(void) const override;
	FrameListAnimation(const std::string& _id,const Frames& _frames,unsigned r, int dx, int dy, unsigned d, bool c);
};

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

#endif _FRAMELISTANIMATION_H_