#ifndef _VIEWWINDOW_H_
#define _VIEWWINDOW_H_

#include "../TypeDefinitions.h"
#include "./Tilemap.h"

void TileTerrainDisplay(TileMap* map, Bitmap dest, const Rect& viewWin, const Rect& displayArea, Bitmap* tiles) {
	if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
		auto startCol = DIV_TILE_WIDTH(viewWin.x);
		auto startRow = DIV_TILE_HEIGHT(viewWin.y);
		auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
		auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
		dpyX = MOD_TILE_WIDTH(viewWin.x);
		dpyY = MOD_TILE_WIDTH(viewWin.y);
		viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;
		std::cout << "Start col: " << startCol << " Start Row: " << startRow << " End col: " << endCol << " EndRow: " << endRow << std::endl;
		for (Dim row = startRow; row <= endRow; ++row)
			for (Dim col = startCol; col <= endCol; ++col)
				PutTile(/*dpyBuffer*/ dest, MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), tiles, GetTile(map, col, row));
	}
}

//!todo
int GetMapPixelWidth(void) {
	return TILEMAP_WIDTH * TILE_WIDTH; //change on define
}

//!todo
int GetMapPixelHeight(void) {
	return TILEMAP_HEIGHT * TILE_HEIGHT;
}

void Scroll(Rect* viewWin, int dx, int dy) {
	viewWin->x += dx; viewWin->y += dy;
}

bool CanScrollHoriz(const Rect& viewWin, int dx) {
	return viewWin.x >= -dx &&
		(viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
}

bool CanScrollVert(const Rect& viewWin, int dy) {
	return viewWin.y >= -dy &&
		(viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
}

static void FilterScrollDistance(int viewStartCoord, /* x or y*/int viewSize, /* w or h*/int* d, /* dx or dy*/ 	int maxMapSize /* w or h*/) {
	auto val = *d + viewStartCoord;
	if (val < 0)
		*d = viewStartCoord; // cross low bound
	else
		if (viewSize >= maxMapSize)// fits entirely
			*d = 0;
		else
			if ((val + viewSize) >= maxMapSize) // cross upper bound
				*d = maxMapSize - (viewStartCoord + viewSize);
}

void FilterScroll(const Rect& viewWin, int* dx, int* dy) {
	FilterScrollDistance(viewWin.x, viewWin.w, dx, GetMapPixelWidth());
	FilterScrollDistance(viewWin.y, viewWin.h, dy, GetMapPixelHeight());
}

void ScrollWithBoundsCheck(Rect* viewWin, int dx, int dy) {
	FilterScroll(*viewWin, &dx, &dy);
	Scroll(viewWin, dx, dy);
}

#endif
/*Section with multiple display methods is not present here.*/


