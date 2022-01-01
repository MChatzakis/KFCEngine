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
//#include "./GridLayer.h"

//This class has all the functions related to tilemap modifications. Made for grouping. Everything is static.
class TileUtilities {
public:
	static byte MakeIndex(byte row, byte col)
	{
		return (col << COL_SHIFT) | row;
		//episis de mas kanei to byte san type
		//return row * TILESET_WIDTH + col;
	}

	static byte GetCol(byte index)
	{
		return index >> COL_SHIFT;
		//return index % TILESET_WIDTH;
	}

	static byte GetRow(byte index)
	{
		return index & ROW_MASK;
		//return index / TILESET_WIDTH;
	}

	static Dim TileX(byte index)
	{
		return GetCol(index) * TILESET_WIDTH;
	}

	static Dim TileY(byte index)
	{
		return GetRow(index) * TILESET_HEIGHT;
	}

	static Dim TileX2(byte index)
	{
		return MUL_TILE_WIDTH(GetCol(index));
	}

	static Dim TileY2(byte index)
	{
		return MUL_TILE_HEIGHT(GetRow(index));
	}

	static Index MakeIndex2(byte row, byte col)
	{
		return (MUL_TILE_WIDTH(col) << TILEX_SHIFT) | MUL_TILE_HEIGHT(row);
	}

	static Dim TileX3(Index index) { return index >> TILEX_SHIFT; }

	static Dim TileY3(Index index) { return index & TILEY_MASK; }

	static Index CustomMakeIndex(Dim row, Dim col)
	{
		return (Index)row * TILESET_WIDTH + col;
	}

	static Dim CustomGetCol(Index index)
	{
		return index % TILESET_WIDTH;
	}

	static Dim CustomGetRow(Index index)
	{
		return index / TILESET_WIDTH;
	}

	static void PutTile(Bitmap dest, Dim x, Dim y, Bitmap* tiles, Index tile) {
		//BitmapBlit(tiles, Rect{ TileX3(tile), TileY3(tile), TILE_WIDTH, TILE_HEIGHT }, dest, Point{ x, y });
		// POIO EINAI TO TARGET DEST GAMW TO SPITAKI?
		//al_draw_bitmap_region((ALLEGRO_BITMAP*)tiles, TileX3(tile) * TILE_WIDTH, TileY3(tile), TILE_WIDTH * TILE_HEIGHT, TILE_HEIGHT, x, y, 0);

		al_draw_bitmap_region((ALLEGRO_BITMAP*)tiles, CustomGetCol(tile) * TILE_WIDTH, CustomGetRow(tile) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, x, y, 0);
	}

	static void SetTile(TileMap* m, Dim col, Dim row, Index index)
	{
		(*m)[row][col] = index;
	}

	static Index GetTile(const TileMap* m, Dim col, Dim row)
	{
		return (*m)[row][col];
	}

	static void WriteBinMap(const TileMap* m, FILE* fp)
	{
		fwrite(m, sizeof(TileMap), 1, fp);
	} // simplistic...

	static bool ReadBinMap(TileMap* m, FILE* fp)
	{ // binary formatted read, like descent parsing
		assert(false);
		return false;
	}

	static void WriteTextMap(const TileMap* m, const char* filename)
	{ // custom write in text format
		std::ofstream fp(filename);
		if (!fp.is_open()) return;

		for (Dim row = 0; row < TILEMAP_HEIGHT; row++) {
			for (Dim column = 0; column < TILEMAP_WIDTH; column++) {
				//read number as a string from fp
				fp << (short)GetTile(m, column, row);
				if (column != TILEMAP_WIDTH - 1)
					fp << ",";
			}
			fp << "\n";
		}
		fp.close();
	}

	/*Nomizw oti afoy paei sto engine prepei na pairnei kai width, height san arguments*/
	static bool ReadTextMap(TileMap* m, const char* filename) {
		Index index;
		Dim row = 0, column = 0;
		std::string line;
		std::ifstream fp(filename);
		if (!fp.is_open()) return false;

		while (std::getline(fp, line)) {
			char* values = strtok((char*)line.c_str(), ",");
			while (values != NULL)
			{
				//printf("%s ", values);
				//[MC] - Patch:
				long currNum = strtol(values, NULL, 0);
				if (currNum >= 0) {
					index = (Index)currNum; //de nomizw na xanei info
					SetTile(m, column, row, index); //pozerilikia..
				}

				column++;
				values = strtok(NULL, ",");
			}
			row++;
			//std::cout <<  "Columns: " << column << std::endl;
			column = 0;
			//printf("\n");
		}
		//std::cout << "Rows: " << row << std::endl;
		fp.close();
		return true;
	}

	static void printTileMap_DEBUG(TileMap* m) {


		for (int i = 0; i < TILEMAP_HEIGHT; i++) {
			std::cout << "[" << i << "]: ";
			for (int j = 0; j < TILEMAP_WIDTH; j++) {
				std::cout << GetTile(m, j, i) << " ";
			}
			std::cout << "\n";
		}
	}
};

//This class has all the functions related to scrolloing and view window. Made for grouping. Everything is static.
class ScrollUtilities {
public:
	static void TileTerrainDisplay(TileMap* map, Bitmap dest, const Rect& viewWin, /*const Rect& displayArea,*/ Bitmap* tiles) {
		if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
			auto startCol = DIV_TILE_WIDTH(viewWin.x);
			auto startRow = DIV_TILE_HEIGHT(viewWin.y);
			auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
			auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
			dpyX = MOD_TILE_WIDTH(viewWin.x);
			dpyY = MOD_TILE_WIDTH(viewWin.y);
			viewPosCached.x = viewWin.x, viewPosCached.y = viewWin.y;

			//std::cout << "Start col: " << startCol << " Start Row: " << startRow << " End col: " << endCol << " EndRow: " << endRow << std::endl;

			for (Dim row = startRow; row <= endRow; ++row)
				for (Dim col = startCol; col <= endCol; ++col)
					TileUtilities::PutTile(/*dpyBuffer*/ dest, MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), tiles, TileUtilities::GetTile(map, col, row));
		}
	}

	static int GetMapPixelWidth(void) {
		return TILEMAP_WIDTH * TILE_WIDTH; //change on define
	}

	static int GetMapPixelHeight(void) {
		return TILEMAP_HEIGHT * TILE_HEIGHT;
	}

	static void Scroll(Rect* viewWin, int dx, int dy) {
		viewWin->x += dx; viewWin->y += dy;
	}

	static bool CanScrollHoriz(const Rect& viewWin, int dx) {
		return viewWin.x >= -dx &&
			(viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
	}

	static bool CanScrollVert(const Rect& viewWin, int dy) {
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

	static void FilterScroll(const Rect& viewWin, int* dx, int* dy) {
		FilterScrollDistance(viewWin.x, viewWin.w, dx, GetMapPixelWidth());
		FilterScrollDistance(viewWin.y, viewWin.h, dy, GetMapPixelHeight());
	}

	static void ScrollWithBoundsCheck(Rect* viewWin, int dx, int dy) {
		FilterScroll(*viewWin, &dx, &dy);
		Scroll(viewWin, dx, dy);
	}

};

//This class represents the whole layer of the tiles
class TileLayer {
private:
	//GridLayer* grid = nullptr;
	TileMap map;

	//Dim totalRows = 0, totalColumns = 0;
	Dim dpyX = 0, dpyY = 0;

	Rect viewWin;

	Bitmap tileSet = nullptr;
	Bitmap dpyBuffer = nullptr;

	bool dpyChanged = true;

	void Allocate(void) {
		//map = new Index[totalRows * totalColumns];
		dpyBuffer = BitmapCreate(GetResWidth() + 2 * TILE_WIDTH, GetResHeight() + 2 * TILE_HEIGHT);
	}

public:
	void * getTileMap() {
		return map;
	}

	void SetTile(Dim col, Dim row, Index index) {
		map[row][col] = index;
	}

	Index GetTile(Dim col, Dim row) const
	{
		return map[row][col];
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

		//dest should be the backbuffer -> dest = al_get_backfuffer(display) from GameMain.

		//al_set_target_bitmap((ALLEGRO_BITMAP*)dest);
		//al_clear_to_color(al_map_rgb(0, 0, 0)); //clear everything

		//ScrollUtilities::TileTerrainDisplay(&map, dest, viewWin, &tileSet); //display
		//ScrollUtilities::TileTerrainDisplay(&map, NULL, viewWin, &tileSet);
		ScrollUtilities::TileTerrainDisplay(&map, NULL, viewWin, &tileSet);


		//flip will be called in game loop.
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
		assert(0); //I am not sure how to implement them here, maybe we should use the ones we created earlier.
	}

	bool CanScrollHoriz(float dx) const {
		assert(0); //I am not sure how to implement them here, maybe we should use the ones we created earlier.
	}

	bool CanScrollVert(float dy) const {
		assert(0); //I am not sure how to implement them here, maybe we should use the ones we created earlier.
	}

	auto ToString(void) const -> const std::string {
		return std::string("To String is not implemented yet!");
	}

	bool FromString(const std::string&) {
		assert(0);
	}

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

	bool ReadText(const char* path) {
		return TileUtilities::ReadTextMap(&map, path);
	}

	//As _rows and _cols is a define, I removed them from here.
	TileLayer(/*Dim _rows, Dim _cols,*/Bitmap _tileSet) {
		//totalRows = _rows;
		//totalColumns = _cols;
		tileSet = _tileSet;
		//std::cout << tileSet << std::endl;
		//std::cout << _tileSet << std::endl;
		Allocate();

	}

	~TileLayer() {
		// call delete 
	}

};


#endif
