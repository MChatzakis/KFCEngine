#ifndef _TILELAYER_H_
#define _TILELAYER_H_

#include <iostream>
#include <functional>
#include <chrono>
#include <fstream>
#include <cstdio>
#include <string>

#include <allegro5/allegro.h>

#include "./General.h"
#include "./GridLayer.h"
#include "./TileUtilities.h"

//This class has all the functions related to scrolloing and view window. Made for grouping. Everything is static. Not to be used..
class ScrollUtilities {
public:
	static void TileTerrainDisplay(TileMap* map, Bitmap dest, const Rect& viewWin, /*const Rect& displayArea,*/ Bitmap tiles);

	static int GetMapPixelWidth(void);

	static int GetMapPixelHeight(void);

	static void Scroll(Rect* viewWin, int dx, int dy);

	static bool CanScrollHoriz(const Rect& viewWin, int dx);

	static bool CanScrollVert(const Rect& viewWin, int dy);

	static void FilterScrollDistance(int viewStartCoord, /* x or y*/int viewSize, /* w or h*/int* d, /* dx or dy*/ 	int maxMapSize /* w or h*/);

	static void FilterScroll(const Rect& viewWin, int* dx, int* dy);

	static void ScrollWithBoundsCheck(Rect* viewWin, int dx, int dy);

};

class TileLayer {
private:
	Index* map = nullptr;
	GridLayer* grid = nullptr;

	Dim totalRows = 0, totalColumns = 0;
	Dim dpyX = 0, dpyY = 0;

	Rect viewWin;

	Bitmap tileSet = nullptr;
	Bitmap dpyBuffer = nullptr;

	bool dpyChanged = true;

	void Allocate(void);

public:
	Dim GetTotalRows();
	Dim GetTotalColumns();

	GridLayer* GetGrid();
	Index* GetTileMap();

	void SetTile(Dim col, Dim row, Index index);
	Index GetTile(Dim col, Dim row) const;

	const Point Pick(Dim x, Dim y) const;
	const Rect& GetViewWindow(void) const;

	void SetViewWindow(const Rect& r);

	void Display(Bitmap dest/*, const Rect& displayArea*/);
	void ConstantDisplay(Bitmap dest);

	Bitmap GetBitmap(void) const;

	int GetPixelWidth(void) const;
	int GetPixelHeight(void) const;

	unsigned GetTileWidth(void) const;
	unsigned GetTileHeight(void) const;

	void Scroll(float dx, float dy);
	int GetMapPixelWidth();
	int GetMapPixelHeight();
	bool CanScrollHoriz(float dx);
	bool CanScrollVert(float dy);
	void FilterScrollDistance(int viewStartCoord, /* x or y*/int viewSize, /* w or h*/int* d, /* dx or dy*/ int maxMapSize /* w or h*/);
	void FilterScroll(int* dx, int* dy);
	void ScrollWithBoundsCheck(int dx, int dy);

	auto ToString(void) const -> const std::string;
	bool FromString(const std::string&);

	void Save(const std::string& path) const;
	bool Load(const std::string& path);

	FILE* WriteText(FILE* fp) const;
	bool ReadText(const char* path);

	TileLayer(Dim _rows, Dim _cols, const Bitmap& _tileSet, const Rect& _viewWin);
	~TileLayer();
};



#endif _TILELAYER_H_
