#ifndef _GRIDLAYER_H_
#define _GRIDLAYER_H_

#include <iostream>
#include "../TypeDefinitions.h"

#include "./Grid.h"

class GridLayer {
private:
	GridIndex* grid = nullptr;
	unsigned total = 0;
	Dim totalRows = 0, totalColumns = 0;
	void Allocate(void) {
		grid = new GridIndex[total = totalRows * totalColumns];
		memset(grid, GRID_EMPTY_TILE, total);
	}
	// TODO: adapt as needed and insert all rest motion control functions 
	// inside the private section
	void FilterGridMotionDown(const Rect& r, int* dy) const;
public:
	void FilterGridMotion(const Rect& r, int* dx, int* dy) const;
	bool IsOnSolidGround(const Rect& r) const { // will need later for gravity
		int dy = 1; // down 1 pixel
		FilterGridMotionDown(r, &dy);
		return dy == 0; // if true IS attached to solid ground
	}
	GridIndex*& GetBuffer(void) { return grid; }
	const GridIndex*& GetBuffer(void) const { return grid; }
	GridLayer(unsigned rows, unsigned cols);
};

#endif