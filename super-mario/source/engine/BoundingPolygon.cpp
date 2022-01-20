#include "./BoundingPolygon.h"
//#include "./General.h"

bool BoundingPolygon::Intersects(const BoundingArea& area) const {
	return area.Intersects(*this);
}

BoundingPolygon* BoundingPolygon::Clone(void) const {
	return new BoundingPolygon(points);
}

BoundingPolygon::BoundingPolygon(const Polygon& _points) : points(_points) {}

bool BoundingPolygon::Intersects(const BoundingBox& box) const {
	return box.Intersects(*this);
}

bool BoundingPolygon::Intersects(const BoundingCircle& circle) const {
	return circle.Intersects(*this);
}

bool BoundingPolygon::Intersects(const BoundingPolygon& poly) const {
	//if any point of polygon2 is in polygon1
	for (Polygon::const_iterator point = poly.points.begin(); point != poly.points.end(); ++point) {
		if (this->In(point->x, point->y)) {
			return true;
		}
	}

	//if any point of polygon1 is in polygon2
	for (Polygon::const_iterator point = points.begin(); point != points.end(); ++point) {
		if (poly.In(point->x, point->y)) {
			return true;
		}
	}

	return false;
}

/*bool BoundingPolygon::In(unsigned x, unsigned y) const { //todo
	Polygon::iterator it;

	for (auto const& i : points){
		//std::cout << it->name;
		if (x > i.x || y < i.y) {
			return false;
		}
	}

	return true;
}*/

bool BoundingPolygon::In(unsigned x, unsigned y) const {
	// There must be at least 3 vertices in polygon
	size_t n = points.size();
	if (n < 3) return false;
	
	// Create a point for line segment from p to infinite
	Point extreme = Point(INT_MAX, y);
	Point p = Point(x, y);
	Point caller;

	// Count intersections of the above line with sides of polygon
	int count = 0;
	Polygon::const_iterator startPoint = points.begin();
	Polygon::const_iterator nextPoint = points.begin();
	++nextPoint;
	for (Polygon::const_iterator point = points.begin(); point != points.end(); ++point) {
		if (nextPoint == points.end()) {
			nextPoint = startPoint;
		}

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (caller.doIntersect(*point, *nextPoint, p, extreme))
		{
			// If the point 'p' is collinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (caller.orientation(*point, p, *nextPoint) == 0)
				if (caller.onSegment(*point, p, *nextPoint))
					return true;
				//return caller.onSegment(*point, p, *nextPoint);

			count++;
		}
		++nextPoint;
	}

	// Return true if count is odd, false otherwise
	return count & 1; // Same as (count%2 == 1)
}
