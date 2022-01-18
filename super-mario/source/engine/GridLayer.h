#ifndef _GRIDLAYER_H_
#define _GRIDLAYER_H_

#include <iostream>
#include <set>

#include "./General.h"
#include "./TileUtilities.h"


#define GRID_ELEMENT_WIDTH 4
#define GRID_ELEMENT_HEIGHT 4

#if TILE_WIDTH % GRID_ELEMENT_WIDTH != 0
#error "TILE_WIDTH % GRID_ELEMENT_WIDTH must be zero!"
#endif

#if TILE_HEIGHT % GRID_ELEMENT_HEIGHT != 0
#error "TILE_HEIGHT % GRID_ELEMENT_HEIGHT must be zero!"
#endif

#define GRID_BLOCK_COLUMNS (TILE_WIDTH / GRID_ELEMENT_WIDTH)
#define GRID_BLOCK_ROWS (TILE_HEIGHT / GRID_ELEMENT_HEIGHT)
#define GRID_ELEMENTS_PER_TILE (GRID_BLOCK_ROWS * GRID_BLOCK_COLUMNS)
#define GRID_MAX_HEIGHT (MAX_HEIGHT * GRID_BLOCK_ROWS)
#define GRID_MAX_WIDTH (MAX_WIDTH * GRID_BLOCK_COLUMNS)

#define GRID_MAP_HEIGHT (TILEMAP_HEIGHT * GRID_BLOCK_ROWS)
#define GRID_MAP_WIDTH (TILEMAP_WIDTH * GRID_BLOCK_COLUMNS)

using GridIndex = byte;

typedef GridIndex GridMap[GRID_MAP_HEIGHT][GRID_MAP_WIDTH];

#define GRID_THIN_AIR_MASK 0x0000 // element is ignored
#define GRID_LEFT_SOLID_MASK 0x0001 // bit 0
#define GRID_RIGHT_SOLID_MASK 0x0002 // bit 1
#define GRID_TOP_SOLID_MASK 0x0004 // bit 2
#define GRID_BOTTOM_SOLID_MASK 0x0008 // bit 3
#define GRID_GROUND_MASK 0x0010 // bit 4, keep objects top / bottom (gravity)
#define GRID_FLOATING_MASK 0x0020 // bit 5, keep objects anywhere inside (gravity)
#define GRID_EMPTY_TILE GRID_THIN_AIR_MASK
#define GRID_SOLID_TILE \
(GRID_LEFT_SOLID_MASK | GRID_RIGHT_SOLID_MASK | GRID_TOP_SOLID_MASK | GRID_BOTTOM_SOLID_MASK)

static GridMap grid = { 0 };

#define MAX_PIXEL_WIDTH MUL_TILE_WIDTH(MAX_WIDTH)
#define MAX_PIXEL_HEIGHT MUL_TILE_HEIGHT(MAX_HEIGHT)
#define DIV_GRID_ELEMENT_WIDTH(i) ((i)>>2) //CCC
#define DIV_GRID_ELEMENT_HEIGHT(i) ((i)>>2)
#define MUL_GRID_ELEMENT_WIDTH(i) ((i)<<2)
#define MUL_GRID_ELEMENT_HEIGHT(i) ((i)<<2)

#define GRID_BLOCK_SIZEOF \
(GRID_ELEMENTS_PER_TILE * sizeof(GridIndex))

#define SetGridTileBlockEmpty(col, row, cols, grid) \
SetGridTileBlock(col, row, cols, grid, GRID_EMPTY_TILE)

#define SetGridTileBlockSolid(col, row, cols, grid) \
SetGridTileBlock(col, row, cols, grid, GRID_SOLID_TILE)

#define GRID_BLOCK_SIZEOF \
(GRID_ELEMENTS_PER_TILE * sizeof(GridIndex))

#define SetGridTileBlockEmpty(col, row, cols, grid) \
SetGridTileBlock(col, row, cols, grid, GRID_EMPTY_TILE)

#define SetGridTileBlockSolid(col, row, cols, grid) \
SetGridTileBlock(col, row, cols, grid, GRID_SOLID_TILE)

class GridUtilities;

class TileColorsHolder final {
private:
	std::set<Index> indices;
	std::set<Color> colors;
public:
	void Insert(Bitmap bmp, Index index);
	bool In(Color c) const;
};

static TileColorsHolder emptyTileColors;

class GridUtilities {
public:
	// 
	static void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index);

	static GridIndex GetGridTile(const GridMap* m, Dim col, Dim row);

	static void SetSolidGridTile(GridMap* m, Dim col, Dim row);

	static void SetEmptyGridTile(GridMap* m, Dim col, Dim row);

	static void SetGridTileFlags(GridMap* m, Dim col, Dim row, GridIndex flags);

	static void SetGridTileTopSolidOnly(GridMap* m, Dim col, Dim row);

	static bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags);

	static void FilterGridMotion(GridMap* m, const Rect& r, int* dx, int* dy);

	static void FilterGridMotionLeft(GridMap* m, const Rect& r, int* dx);

	static void FilterGridMotionUp(GridMap* m, const Rect& r, int* dy);

	static void FilterGridMotionDown(GridMap* m, const Rect& r, int* dy);

	static void FilterGridMotionRight(GridMap* m, const Rect& r, int* dx);

	static bool IsTileIndexAssumedEmpty(Index index);

	static void ComputeTileGridBlocks1(const TileMap* map, GridIndex* grid);

	static bool IsTileColorEmpty(Color c);

	static void ComputeTileGridBlocks2(const TileMap* map, GridIndex* grid, Bitmap tileSet, Color transColor, byte solidThreshold);

	static void ComputeGridBlock(GridIndex*& grid, Index index, Bitmap tileElem, Bitmap gridElem, Bitmap tileSet, Color transColor, byte solidThreshold);

	static Color GetPixel32(PixelMemory mem);

	static bool ComputeIsGridIndexEmpty(Bitmap gridElement, Color transColor, byte solidThreshold);

	static GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid);

	static void SetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid, GridIndex flags);

	// use this to render grid (toggle on / off), used only for development time testing -
	// a tile grid block is consecutive GRID_BLOCK_ROWS x GRID_BLOCK_COLUMNS block of grid indices
	template <typename Tfunc> static void DisplayGrid(Bitmap dest, const Rect& viewWin, GridIndex* grid, Dim tileCols, const Tfunc& display_f);

	static void DisplayGrid(Bitmap dest, const Rect& viewWin, GridIndex* grid, Dim tileCols);
};

class GridLayer {
private:
	GridIndex* grid = nullptr;

	unsigned total = 0;

	Dim totalRows = 0, totalColumns = 0;

	//ok
	void Allocate(void);

	//ok
	void FilterGridMotionLeft(const Rect& r, int* dx);

	//ok
	void FilterGridMotionUp(const Rect& r, int* dy);

	//ok
	void FilterGridMotionDown(const Rect& r, int* dy);

	//ok
	void FilterGridMotionRight(const Rect& r, int* dx);

public:
	//ok
	void SetGridTile(Dim col, Dim row, GridIndex index);

	//ok
	GridIndex GetGridTile(Dim col, Dim row);

	//ok
	void SetSolidGridTile(Dim col, Dim row);

	//ok
	void SetEmptyGridTile(Dim col, Dim row);

	//ok
	void SetGridTileFlags(Dim col, Dim row, GridIndex flags);

	//ok
	void SetGridTileTopSolidOnly(Dim col, Dim row);

	//ok
	bool CanPassGridTile(Dim col, Dim row, GridIndex flags);

	//ok
	void FilterGridMotion(const Rect& r, int* dx, int* dy);

	//ok
	bool IsOnSolidGround(const Rect& r);

	//ok
	GridIndex* GetBuffer(void);

	//ok
	bool IsTileIndexAssumedEmpty(Index index);

	//ok
	const GridIndex*& GetBuffer(void) const;

	//ok
	GridLayer(unsigned rows, unsigned cols);
};


#endif _GRIDLAYER_H_