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


#endif _BOUNDINGBOX_H_