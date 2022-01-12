#ifndef _BOUNDINGAREA_H_
#define _BOUNDINGAREA_H_

class BoundingBox;
class BoundingCircle;
class BoundingPolygon;

class BoundingArea {
protected:
	virtual bool Intersects(const BoundingBox& box) const = 0;
	virtual bool Intersects(const BoundingCircle& circle) const = 0;
	virtual bool Intersects(const BoundingPolygon& poly) const = 0;

public:
	virtual bool In(unsigned x, unsigned y) const = 0;
	virtual bool Intersects(const BoundingArea& area) const = 0;
	virtual BoundingArea* Clone(void) const;
	virtual ~BoundingArea() {}
};

#endif _BOUNDINGAREA_H_