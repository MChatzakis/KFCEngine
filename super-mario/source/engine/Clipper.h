#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include <iostream>
#include <functional>
#include <algorithm>

#include "./General.h"

template <class T> bool clip_rect(T x, T y, T w, T h, T wx, T wy, T ww, T wh, T* cx, T* cy, T* cw, T* ch);

bool clip_rect(const Rect& r, const Rect& area, Rect* result);

class Clipper {
public:
	using View = std::function<const Rect& (void)>;
private:
	View view;
public:
	Clipper& SetView(const View& f);
	bool Clip(const Rect& r, const Rect& dpyArea, Point* dpyPos, Rect* clippedBox) const;

	Clipper(void) = default;
	Clipper(const Clipper&) = default;
};

#endif _CLIPPER_H_
