#ifndef _MOTIONQUANTIZER_H_
#define _MOTIONQUANTIZER_H_

#include <iostream>
#include <functional>
#include <algorithm>

#include "./General.h"


class MotionQuantizer {
public:
	using Mover = std::function<void(const Rect& r, int* dx, int* dy)>;
protected:
	int horizMax = 0, vertMax = 0;
	Mover mover; // filters requested motion too!
	bool used = false;
public:
	MotionQuantizer& SetUsed(bool val);

	MotionQuantizer& SetRange(int h, int v);
	MotionQuantizer& SetMover(const Mover& f);

	void Move(const Rect& r, int* dx, int* dy);

	MotionQuantizer(void) = default;
	MotionQuantizer(const MotionQuantizer&) = default;
};


#endif _MOTIONQUANTIZER_H_