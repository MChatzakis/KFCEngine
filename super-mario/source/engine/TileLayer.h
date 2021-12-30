#ifndef _TILELAYER_H_
#define _TILELAYER_H_

#include <iostream>

#include "./General.h"
#include "./GridLayer.h"

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

/*void Scroll(Rect* viewWin, int dx, int dy) {
	viewWin->x += dx; viewWin->y += dy;
}

bool CanScrollHoriz(const Rect& viewWin, int dx) {
	return viewWin.x >= -dx &&
		(viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
}*

bool CanScrollVert(const Rect& viewWin, int dy) {
	return viewWin.y >= -dy &&
		(viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
}*/

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

class TileLayer {
private:
	GridLayer* grid = nullptr;

	Index* map = nullptr;

	Dim totalRows = 0, totalColumns = 0;
	Dim dpyX = 0, dpyY = 0;

	Rect viewWin;

	Bitmap tileSet = nullptr;
	Bitmap dpyBuffer = nullptr;

	bool dpyChanged = true;

	void Allocate(void) {
		map = new Index[totalRows * totalColumns];
		dpyBuffer = BitmapCreate(GetResWidth() + 2 * TILE_WIDTH, GetResHeight() + 2 * TILE_HEIGHT);
	}

public:
	void SetTile(Dim col, Dim row, Index index) {
		map[row * totalColumns + col] = index;
	}

	Index GetTile(Dim col, Dim row) const
	{
		return map[row * totalColumns + col];
	}

	const Point Pick(Dim x, Dim y) const {
		return { DIV_TILE_WIDTH(x + viewWin.x),	DIV_TILE_HEIGHT(y + viewWin.y) };
	}

	const Rect& GetViewWindow(void) const {
		return viewWin;
	}

	void SetViewWindow(const Rect& r)
	{
		viewWin = r;
		dpyChanged = true;
	}

	void Display(Bitmap dest, const Rect& displayArea) {
		assert(0);
		al_draw_bitmap((ALLEGRO_BITMAP*)dest, displayArea.x, displayArea.y, 0);

	}

	Bitmap GetBitmap(void) const {
		return dpyBuffer;
	}

	int GetPixelWidth(void) const {
		return viewWin.w;
	}

	int GetPixelHeight(void) const {
		return viewWin.h;
	}

	unsigned GetTileWidth(void) const {
		return DIV_TILE_WIDTH(viewWin.w);
	}

	unsigned GetTileHeight(void) const {
		return DIV_TILE_HEIGHT(viewWin.h);
	}

	//ok
	void Scroll(float dx, float dy) {
		viewWin.x += dx; 
		viewWin.y += dy;
	}

	bool CanScrollHoriz(float dx) const {
		return viewWin.x >= -dx && (viewWin.x + viewWin.w + dx) <= GetMapPixelWidth(); //?
	}

	bool CanScrollVert(float dy) const {
		return viewWin.y >= -dy && (viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
	}

	auto ToString(void) const -> const std::string {
		return std::string("To String is not implemented yet!");
	}// unparse

	bool FromString(const std::string&) {
		assert(0);
	} // parse

	void Save(const std::string& path) const
	{
		fclose(WriteText(fopen(path.c_str(), "wt")));
	}

	bool Load(const std::string& path) {
		assert(0);
	}

	FILE* WriteText(FILE* fp) const
	{
		fprintf(fp, "%s", ToString().c_str()); return fp;
	}

	bool ReadText(FILE* fp) {
		assert(0);
	}

	//ok
	TileLayer(Dim _rows, Dim _cols, Bitmap _tileSet) {
		totalRows = _rows;
		totalColumns = _cols;
		tileSet =_tileSet;
		
		Allocate();

	}

	~TileLayer() {
		
	}

};


#endif
