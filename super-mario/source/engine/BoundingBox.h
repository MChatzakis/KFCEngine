#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "./BoundingArea.h"
#include "./BoundingCircle.h"
#include "./BoundingPolygon.h"

class BoundingBox : public BoundingArea {
protected:
	unsigned x1, y1, x2, y2;
public:
	virtual bool Intersects(const BoundingBox& box) const = 0;
	virtual bool Intersects(const BoundingCircle& circle) const = 0;
	virtual bool Intersects(const BoundingPolygon& poly) const = 0;

	virtual bool In(unsigned x, unsigned y) const;
	virtual bool Intersects(const BoundingArea& area) const;

	virtual BoundingBox* Clone(void) const;

	BoundingBox(unsigned _x1, unsigned _y1, unsigned _x2, unsigned _y2);
};

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
	points.push_back(BoundingPolygon::Point(x1, y1));
	points.push_back(BoundingPolygon::Point(x2, y2));
	BoundingPolygon selfPoly(points);

	return poly.Intersects(selfPoly);
}

bool BoundingBox::In(unsigned x, unsigned y) const {
	retrunn x1 <= x && x <= x2 && y1 <= y && y <= y1;
}


#endif _BOUNDINGBOX_H_