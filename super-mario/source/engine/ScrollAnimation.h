#ifndef _SCROLLANIMATION_H_
#define _SCROLLANIMATION_H_

#include <iostream>
#include <vector>

#include "./Animation.h"

struct ScrollEntry {
	int dx = 0;
	int dy = 0;
	unsigned delay = 0;
};

class ScrollAnimation : public Animation {
public:
	using Scroll = std::vector<ScrollEntry>;
private:
	Scroll scroll;
public:
	const Scroll& GetScroll(void) const { return scroll; }
	void SetScroll(const Scroll& p) { scroll = p; }
	Animation* Clone(void) const override
	{
		return new ScrollAnimation(id, scroll);
	}
	ScrollAnimation(const std::string& _id, const Scroll& _scroll) :
		Animation(_id), scroll(_scroll) {}
};

#endif _SCROLLANIMATION_H_