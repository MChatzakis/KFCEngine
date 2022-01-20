#include "./BoundingCircle.h"
#include "./General.h"

#include <math.h>

bool BoundingCircle::Intersects(const BoundingArea& area) const {
	return area.Intersects(*this);
}

BoundingCircle* BoundingCircle::Clone(void) const {
	return new BoundingCircle(x, y, r);
}

BoundingCircle::BoundingCircle(unsigned _x, unsigned _y, unsigned _r) : x(_x), y(_y), r(_r) {}

bool BoundingCircle::In(unsigned _x, unsigned _y) const {
	return pow(x - _x, 2) + pow(y - _y, 2) <= pow(r, 2);
}

bool BoundingCircle::Intersects(const BoundingBox& box) const { //todo
	if (Point::pointDistance(Point(x, y), box.GetCenterPoint()) > r + box.GetDiagonal() / 2) {
		return false;
	}
	else {
		assert(0);
	}

	return true;
}

bool BoundingCircle::Intersects(const BoundingPolygon& poly) const { //todo
	assert(0);
	return false;
}

bool BoundingCircle::Intersects(const BoundingCircle& circle) const {
	return  Point::pointDistance(Point(x, y), Point(circle.x, circle.y)) < ((double)r + (double)circle.r); //what about <=?
}