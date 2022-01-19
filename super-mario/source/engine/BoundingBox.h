#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include <math.h>

#include "./BoundingArea.h"
#include "./BoundingCircle.h"
#include "./BoundingPolygon.h"
#include "./General.h"

class BoundingBox : public BoundingArea {
protected:
	unsigned x1, y1, x2, y2;
public:
	virtual bool Intersects(const BoundingBox& box) const;
	virtual bool Intersects(const BoundingCircle& circle) const;
	virtual bool Intersects(const BoundingPolygon& poly) const;

	virtual bool In(unsigned x, unsigned y) const;
	virtual bool Intersects(const BoundingArea& area) const;

	virtual BoundingBox* Clone(void) const;

	BoundingBox(unsigned _x1, unsigned _y1, unsigned _x2, unsigned _y2);

	virtual Point GetCenterPoint() const{
		double width = abs((double) (x2 - x1));
		double height = abs((double) (y2 - y1));
		return Point(x1 + width/2, y1 + height/2);
	}

	virtual double GetDiagonal() const {
		double width = abs((double)(x2 - x1));
		double height = abs((double)(y2 - y1));
		return sqrt(pow(width, 2) + pow(height, 2));
	}
};


#endif _BOUNDINGBOX_H_