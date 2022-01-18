#ifndef _BOUNDINGPOLYGON_H_
#define _BOUNDINGPOLYGON_H_

#include <iostream>
#include <list>

#include "./BoundingArea.h"


class BoundingPolygon : public BoundingArea {
public:
	struct Point {
		unsigned x, y;
		Point(void) : x(0), y(0) {}
		Point(unsigned _x, unsigned _y) : x(_x), y(_y) {}
		Point(const Point& p) : x(p.x), y(p.y) {}
	};
	typedef std::list<Point>Polygon;

protected:
	Polygon points;
public:
	virtual bool Intersects(const BoundingBox& box) const;
	virtual bool Intersects(const BoundingCircle& circle) const;
	virtual bool Intersects(const BoundingPolygon& poly) const;

	virtual bool In(unsigned x, unsigned y) const;
	virtual bool Intersects(const BoundingArea& area) const;

	virtual BoundingPolygon* Clone(void) const;

	BoundingPolygon(const Polygon& _points);
};


#endif _BOUNDINGPOLYGON_H_