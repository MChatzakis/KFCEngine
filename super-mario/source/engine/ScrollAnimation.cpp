#include "./ScrollAnimation.h"

const ScrollAnimation::Scroll&
ScrollAnimation::GetScroll(void) const { return scroll; }

void
ScrollAnimation::SetScroll(const Scroll& p) { scroll = p; }

Animation*
ScrollAnimation::Clone(void) const //override
{
	return new ScrollAnimation(id, scroll);
}

ScrollAnimation::ScrollAnimation(const std::string& _id, const Scroll& _scroll) :
	Animation(_id), scroll(_scroll) {}