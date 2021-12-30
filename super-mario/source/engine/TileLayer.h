#ifndef _TILELAYER_H_
#define _TILELAYER_H_

#include <iostream>

#include "./General.h"
#include "./GridLayer.h"

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

	void Scroll(float dx, float dy) {
		assert(0);
	}

	bool CanScrollHoriz(float dx) const {
		assert(0);
	}

	bool CanScrollVert(float dy) const {
		assert(0);
	}

	auto ToString(void) const -> const std::string {
		assert(0);
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
	} // TODO: carefull generic parsing

	TileLayer(Dim _rows, Dim _cols, Bitmap _tileSet) {
		assert(0);
	}

	~TileLayer() {
		assert(0);
	}// cleanup here with care!

};


#endif
