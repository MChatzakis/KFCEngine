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

#endif _FRAMELISTANIMATION_H_