#include "./BoundingBox.h"

bool BoundingBox::Intersects(const BoundingArea& area) const {
	return area.Intersects(*this);
}

BoundingBox* BoundingBox::Clone(void) const {
	return new BoundingBox(x1, y1, x2, y2);
}

BoundingBox::BoundingBox(unsigned _x1, unsigned _y1, unsigned _x2, unsigned _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

bool BoundingBox::Intersects(const BoundingBox& box) const {
	return !(box.x2 < x1 || x2 < box.x1 || box.y2 < y1 || y2 < box.y1);
}

bool BoundingBox::Intersects(const BoundingCircle& circle) const {
	return circle.Intersects(*this);
}

bool BoundingBox::Intersects(const BoundingPolygon& poly) const {
	BoundingPolygon::Polygon points;

	points.push_back(/*BoundingPolygon::*/Point(x1, y1));
	points.push_back(/*BoundingPolygon::*/Point(x1, y2));
	points.push_back(/*BoundingPolygon::*/Point(x2, y2));
	points.push_back(/*BoundingPolygon::*/Point(x2, y1)); //convert box to polygon

	BoundingPolygon selfPoly(points);

	return poly.Intersects(selfPoly);
}

bool BoundingBox::In(unsigned x, unsigned y) const {
	return x1 <= x && x <= x2 && y1 <= y && y <= y2;
}
