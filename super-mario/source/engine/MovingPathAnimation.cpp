#include "./MovingPathAnimation.h"

const MovingPathAnimation::Path&
MovingPathAnimation::GetPath(void) const { return path; }

void
MovingPathAnimation::SetPath(const Path& p) { path = p; }

Animation*
MovingPathAnimation::Clone(void) const //override
{
	return new MovingPathAnimation(id, path);
}

MovingPathAnimation::MovingPathAnimation(const std::string& _id, const Path& _path) :
	path(_path), Animation(id) {}