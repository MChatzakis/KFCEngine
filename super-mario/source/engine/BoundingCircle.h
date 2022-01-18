#ifndef _BOUNDINGCIRCLE_H_
#define _BOUNDINGCIRCLE_H_

#include "./BoundingArea.h"

class BoundingCircle : public BoundingArea {
protected:
	unsigned x, y, r;
public:
	virtual bool Intersects(const BoundingBox& box) const;
	virtual bool Intersects(const BoundingCircle& circle) const;
	virtual bool Intersects(const BoundingPolygon& poly) const;

	virtual bool In(unsigned x, unsigned y) const;
	virtual bool Intersects(const BoundingArea& area) const;

	virtual BoundingCircle* Clone(void) const;

	BoundingCircle(unsigned _x, unsigned _y, unsigned _r);
};

#endif _BOUNDINGCIRCLE_H_