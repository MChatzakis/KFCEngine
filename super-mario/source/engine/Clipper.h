#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include <iostream>
#include <functional>
#include <algorithm>

#include "./General.h"

class Clipper {
public:
	using View = std::function<const Rect& (void)>;
private:
	View view;
public:
	Clipper& SetView(const View& f);
	bool Clip(const Rect& r,const Rect& dpyArea,Point* dpyPos,Rect* clippedBox) const;
	Clipper(void) = default;
	Clipper(const Clipper&) = default;
};

#endif _CLIPPER_H_
