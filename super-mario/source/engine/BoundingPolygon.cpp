#include "./BoundingPolygon.h"

bool BoundingPolygon::Intersects(const BoundingArea& area) const {
	return area.Intersects(*this);
}

BoundingPolygon* BoundingPolygon::Clone(void) const {
	return new BoundingPolygon(points);
}

BoundingPolygon::BoundingPolygon(const Polygon& _points) : points(_points) {}

bool BoundingPolygon::Intersects(const BoundingBox& box) const {
	return false;
}

bool BoundingPolygon::Intersects(const BoundingCircle& circle) const {
	return false;
}

bool BoundingPolygon::Intersects(const BoundingPolygon& poly) const {
	return false;
}

bool BoundingPolygon::In(unsigned x, unsigned y) const {
	Polygon::iterator it;

	for (auto const& i : points){
		//std::cout << it->name;
		if (x > i.x || y < i.y) {
			return false;
		}
	}

	return true;
}
