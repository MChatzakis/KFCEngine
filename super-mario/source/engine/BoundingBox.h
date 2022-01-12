#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include "./BoundingArea.h"

class BoundingBox : public BoundingArea {
protected:
	unsigned x1, y1, x2, y2;
public:
	virtual bool Intersects(const BoundingBox& box) const = 0;
	virtual bool Intersects(const BoundingCircle& circle) const = 0;
	virtual bool Intersects(const BoundingPolygon& poly) const = 0;

	virtual bool In(unsigned x, unsigned y) const;
	virtual bool Intersects(const BoundingArea& area) const {
		return area.Intersects(*this);
	}
};

#endif _BOUNDINGBOX_H_