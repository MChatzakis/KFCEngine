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
	static void SetGridTile(GridMap* m, Dim col, Dim row, GridIndex index)
	{
		(*m)[row][col] = index;
	}

	static GridIndex GetGridTile(const GridMap* m, Dim col, Dim row)
	{
		return (*m)[row][col];
	}

	static void SetSolidGridTile(GridMap* m, Dim col, Dim row)
	{
		SetGridTile(m, col, row, GRID_SOLID_TILE);
	}

	static void SetEmptyGridTile(GridMap* m, Dim col, Dim row)
	{
		SetGridTile(m, col, row, GRID_EMPTY_TILE);
	}

	static void SetGridTileFlags(GridMap* m, Dim col, Dim row, GridIndex flags)
	{
		SetGridTile(m, col, row, flags);
	}

	static void SetGridTileTopSolidOnly(GridMap* m, Dim col, Dim row)
	{
		SetGridTileFlags(m, row, col, GRID_TOP_SOLID_MASK);
	}

	static bool CanPassGridTile(GridMap* m, Dim col, Dim row, GridIndex flags) // i.e. checks if flags set
	{
		bool res = (bool)(*GetGridTileBlock(col/4, row/4, TILEMAP_WIDTH, **m) & flags);
		//res = GetGridTile(m, col, row) & flags;
		if (res)
			std::cout << "You go on Solid tile " << "(" << row << "," << col << ")\n";
			
		return !res; //now it returns 1 on empty tiles
		//return GetGridTile(m, row, col) & (flags != 0);
	}

	static void FilterGridMotion(GridMap* m, const Rect& r, int* dx, int* dy) {
		assert(abs(*dx) <= GRID_ELEMENT_WIDTH && abs(*dy) <= GRID_ELEMENT_HEIGHT);
		// try horizontal move
		if (*dx < 0)
			FilterGridMotionLeft(m, r, dx);
		else
			if (*dx > 0)
				FilterGridMotionRight(m, r, dx);
		// try vertical move
		if (*dy < 0)
			FilterGridMotionUp(m, r, dy);
		else
			if (*dy > 0)
				FilterGridMotionDown(m, r, dy);
	}

	static void FilterGridMotionLeft(GridMap* m, const Rect& r, int* dx) {
		auto x1 = r.x;
		auto x1_next = x1 + *dx;
		if (x1_next < 0)
			*dx = *dx - x1_next; //goes full left
		else {
			auto newCol = DIV_GRID_ELEMENT_WIDTH(x1_next);
			auto currCol = DIV_GRID_ELEMENT_WIDTH(x1);
			if (newCol != currCol) {
				assert(newCol + 1 == currCol); // we really move left
				auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y);
				auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1);
				for (auto row = startRow; row <= endRow; ++row)
					if (!CanPassGridTile(m, newCol, row, GRID_RIGHT_SOLID_MASK)) {
						*dx = MUL_GRID_ELEMENT_WIDTH(currCol) - x1;
						break;
					}
			}
		}
	}

	static void FilterGridMotionUp(GridMap* m, const Rect& r, int* dy) {
		auto y2 = r.y;
		auto y2_next = y2 + *dy;
		//auto y1_next = r.y + *dy;
		if (y2_next < 0)
			*dy = *dy - y2_next; //goes full top
		else {
			auto newRow = DIV_GRID_ELEMENT_HEIGHT(y2_next);
			auto currRow = DIV_GRID_ELEMENT_HEIGHT(y2);
			if (newRow != currRow) {
				assert(newRow == currRow - 1); // we really move up
				auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x);
				auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1);
				for (auto col = startCol; col <= endCol; ++col)
					if (!CanPassGridTile(m, col, newRow, GRID_BOTTOM_SOLID_MASK)) {
						*dy = MUL_GRID_ELEMENT_HEIGHT(currRow) - y2; //sigoura swsta ayta? -1?
						break;
					}
			}
		}
	}

	static void FilterGridMotionDown(GridMap* m, const Rect& r, int* dy) {
		auto y1 = r.y + r.h - 1;
		auto y1_next = y1 + *dy;
		if (y1_next >= MAX_PIXEL_HEIGHT)
			*dy = (MAX_PIXEL_HEIGHT - 1) - y1; //goes full down
		else {
			auto newRow = DIV_GRID_ELEMENT_HEIGHT(y1_next);
			auto currRow = DIV_GRID_ELEMENT_HEIGHT(y1);
			if (newRow != currRow) {
				assert(newRow == currRow + 1); // we really move down
				auto startCol = DIV_GRID_ELEMENT_WIDTH(r.x);
				auto endCol = DIV_GRID_ELEMENT_WIDTH(r.x + r.w - 1);
				for (auto col = startCol; col <= endCol; ++col)
					if (!CanPassGridTile(m, col, newRow, GRID_TOP_SOLID_MASK)) {
						*dy = MUL_GRID_ELEMENT_HEIGHT(newRow) - y1 - 1; //sigoura swsta ayta?
						break;
					}
			}
		}
	}

	static void FilterGridMotionRight(GridMap* m, const Rect& r, int* dx) {
		auto x2 = r.x + r.w - 1;
		auto x2_next = x2 + *dx;
		if (x2_next >= MAX_PIXEL_WIDTH) {
			*dx = (MAX_PIXEL_WIDTH - 1) - x2; //goes full right
			std::cout << "kseperase to orio deksia\n";
		}
		else {
			auto newCol = DIV_GRID_ELEMENT_WIDTH(x2_next);
			auto currCol = DIV_GRID_ELEMENT_WIDTH(x2);
			if (newCol != currCol) {
				assert(newCol - 1 == currCol); // we really move right
				auto startRow = DIV_GRID_ELEMENT_HEIGHT(r.y);
				auto endRow = DIV_GRID_ELEMENT_HEIGHT(r.y + r.h - 1);
				for (auto row = startRow; row <= endRow; ++row)
					if (!CanPassGridTile(m, newCol, row, GRID_LEFT_SOLID_MASK)) {
						*dx = (MUL_GRID_ELEMENT_WIDTH(newCol) - 1) - x2; //sigoura swsta ayta ?
						//*dx = (MUL_GRID_ELEMENT_WIDTH(newCol) - 0) - x2; //sigoura swsta ayta ?
						std::cout << "synantise solid tile\n";
						break;
					}
			}
		}
	}

	static bool IsTileIndexAssumedEmpty(Index index) {
		for (int i = 0; i < TOTAL_EMPTY_INDICES; i++) {
			if (EMPTY_INDICES[i] == index) {
				return true;
			}
		}
		return false;
	}

	static void ComputeTileGridBlocks1(const TileMap* map, GridIndex* grid) {
		for (auto row = 0; row < TILEMAP_HEIGHT; ++row) //change
			for (auto col = 0; col < TILEMAP_WIDTH; ++col) {
				memset(grid, IsTileIndexAssumedEmpty(TileUtilities::GetTile(map, col, row)) ? GRID_EMPTY_TILE : GRID_SOLID_TILE, GRID_ELEMENTS_PER_TILE);
				//memset()
				grid += GRID_ELEMENTS_PER_TILE;
			}
	}

	static bool IsTileColorEmpty(Color c)
	{
		return emptyTileColors.In(c);
		//return false;
	} // return false to disable

	//ti sto diaolo?
	static void ComputeTileGridBlocks2(const TileMap* map, GridIndex* grid, Bitmap tileSet, Color transColor, byte solidThreshold) {
		auto tileElem = al_create_bitmap(TILE_WIDTH, TILE_HEIGHT);
		auto gridElem = al_create_bitmap(GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT);
		for (auto row = 0; row < MAX_HEIGHT; ++row)
			for (auto col = 0; col < MAX_WIDTH; ++col) {
				auto index = TileUtilities::GetTile(map, col, row);
				TileUtilities::PutTile(tileElem, 0, 0, tileSet, index);
				if (IsTileIndexAssumedEmpty(index)) {
					emptyTileColors.Insert(tileElem, index); // assume tile colors to be empty
					memset(grid, GRID_EMPTY_TILE, GRID_ELEMENTS_PER_TILE);
					grid += GRID_ELEMENTS_PER_TILE;
				}
				else
					ComputeGridBlock(// auto increments grid as T*& 
						grid, index, tileElem, gridElem,
						tileSet, transColor, solidThreshold
					);
			}
		al_destroy_bitmap(tileElem);
		al_destroy_bitmap(gridElem);
	}

	//ti sto diaolo?
	static void ComputeGridBlock(GridIndex*& grid, Index index, Bitmap tileElem, Bitmap gridElem, Bitmap tileSet, Color transColor, byte solidThreshold) {
		for (auto i = 0; i < GRID_ELEMENTS_PER_TILE; ++i) {
			auto x = i % GRID_BLOCK_ROWS;
			auto y = i / GRID_BLOCK_ROWS;
			BitmapBlit(
				tileElem,
				{ x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT },
				gridElem,
				{ 0, 0 }
			);
			//al_draw_bitmap_region((ALLEGRO_BITMAP*)tileElem, x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT,/*gridElem*/ 0, 0, 0);

			auto isEmpty = ComputeIsGridIndexEmpty(gridElem, transColor, solidThreshold);
			*grid++ = isEmpty ? GRID_EMPTY_TILE : GRID_SOLID_TILE;
		}
	}

	static Color GetPixel32(PixelMemory mem) {
		RGBA c;
		ReadPixelColor32(mem, &c, &c.a);

		//return MakeColor32(c.r, c.g, c.b, c.a);
		return Make32(c.r, c.g, c.b, c.a);
	}

	static bool ComputeIsGridIndexEmpty(Bitmap gridElement, Color transColor, byte solidThreshold) {
		auto n = 0;
		BitmapAccessPixels(
			gridElement,
			[transColor, &n](PixelMemory* mem) {
				auto c = GetPixel32(*mem);
				//std::cout << "Color inside func " << c << "\n";
				if (c != transColor && !IsTileColorEmpty(c))
					++n;
			}
		);
		return n <= solidThreshold;
	}

	//5*15 (0,14) (1,15) 

	static GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid) {
		return grid + (rowTile * tileCols + colTile) * GRID_BLOCK_SIZEOF;

	}

	static void SetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid, GridIndex flags) {
		memset(GetGridTileBlock(colTile, rowTile, tileCols, grid), flags, GRID_BLOCK_SIZEOF);
	}

	/*static GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid) {
		return grid + (rowTile * tileCols + colTile) * GRID_BLOCK_SIZEOF;
	}

	static void SetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid, GridIndex flags) {
		memset(GetGridTileBlock(colTile, rowTile, tileCols, grid), flags, GRID_BLOCK_SIZEOF);
	}*/

	// use this to render grid (toggle on / off), used only for development time testing -
	// a tile grid block is consecutive GRID_BLOCK_ROWS x GRID_BLOCK_COLUMNS block of grid indices
	template <typename Tfunc> static void DisplayGrid(Bitmap dest, const Rect& viewWin, GridIndex* grid, Dim tileCols, const Tfunc& display_f) {
		auto startCol = DIV_TILE_WIDTH(viewWin.x);
		auto startRow = DIV_TILE_HEIGHT(viewWin.y);
		auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
		auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
		for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile)
			for (Dim colTile = startCol; colTile <= endCol; ++colTile) {
				auto sx = MUL_TILE_WIDTH(colTile - startCol);
				auto sy = MUL_TILE_HEIGHT(rowTile - startRow);
				auto* gridBlock = GetGridTileBlock(colTile, rowTile, tileCols, grid);
				for (auto rowElem = 0; rowElem < GRID_BLOCK_ROWS; ++rowElem)
					for (auto colElem = 0; colElem < GRID_BLOCK_COLUMNS; ++colElem)
						if (*gridBlock++ & GRID_SOLID_TILE) {
							auto x = sx + MUL_GRID_ELEMENT_WIDTH(colElem);
							auto y = sy + MUL_GRID_ELEMENT_HEIGHT(rowElem);
							auto w = GRID_ELEMENT_WIDTH;
							auto h = GRID_ELEMENT_HEIGHT;
							display_f(dest, x, y, w, h);
						}
			}
	}

	static void DisplayGrid(Bitmap dest, const Rect& viewWin, GridIndex* grid, Dim tileCols) {
		auto startCol = DIV_TILE_WIDTH(viewWin.x);
		auto startRow = DIV_TILE_HEIGHT(viewWin.y);
		auto endCol = DIV_TILE_WIDTH(viewWin.x + viewWin.w - 1);
		auto endRow = DIV_TILE_HEIGHT(viewWin.y + viewWin.h - 1);
		for (Dim rowTile = startRow; rowTile <= endRow; ++rowTile)
			for (Dim colTile = startCol; colTile <= endCol; ++colTile) {
				auto sx = MUL_TILE_WIDTH(colTile - startCol);
				auto sy = MUL_TILE_HEIGHT(rowTile - startRow);
				auto* gridBlock = GetGridTileBlock(colTile, rowTile, tileCols, grid);
				for (auto rowElem = 0; rowElem < GRID_BLOCK_ROWS; ++rowElem)
					for (auto colElem = 0; colElem < GRID_BLOCK_COLUMNS; ++colElem) {
						//assert(gridBlock == nullptr);
						if (*gridBlock++ & GRID_SOLID_TILE) {
							auto x = sx + MUL_GRID_ELEMENT_WIDTH(colElem);
							auto y = sy + MUL_GRID_ELEMENT_HEIGHT(rowElem);
							auto w = GRID_ELEMENT_WIDTH;
							auto h = GRID_ELEMENT_HEIGHT;

							al_draw_rectangle(x, y, x + w, y + h, al_map_rgb(0, 0, 0), 1.0);
						}
					}
			}
	}
};

void TileColorsHolder::Insert(Bitmap bmp, Index index) {
	if (indices.find(index) == indices.end()) {
		indices.insert(index);
		BitmapAccessPixels(bmp,
			[this](PixelMemory* mem)
			{ colors.insert(GridUtilities::GetPixel32(*mem)); }
		);
	}
}
bool TileColorsHolder::In(Color c) const
{
	return colors.find(c) != colors.end();
}

/*
1) Finish Unit Test 2. [aurio oloi]
2) Finish GridLayer class [manos] ok alla na to doume mazi me to compile error
3) Other screens and new map
*/

class GridLayer {
private:
	//GridIndex* grid = nullptr;
	GridMap grid;
	Dim totalRows = GRID_MAX_HEIGHT, totalColumns = GRID_MAX_WIDTH; //check again!
	unsigned total = totalRows * totalColumns;

	void Allocate(void) {
		//grid = new GridIndex[total = totalRows * totalColumns];
		memset(grid, GRID_EMPTY_TILE, total);
	}

	// TODO: adapt as needed and insert all rest motion control functions
	// inside the private section
	void FilterGridMotionDown(const Rect& r, int* dy) const {
		const GridMap* pGrid = &grid;
		GridUtilities::FilterGridMotionDown((GridMap*)pGrid, r, dy); //tosee
		//GridUtilities::FilterGridMotionDown(grid, r, dy); //tosee
	}

	void FilterGridMotionUp(const Rect& r, int* dy) const {
		const GridMap* pGrid = &grid;
		GridUtilities::FilterGridMotionUp((GridMap*)pGrid, r, dy);
	}

	void FilterGridMotionLeft(const Rect& r, int* dx) const {
		const GridMap* pGrid = &grid;
		GridUtilities::FilterGridMotionLeft((GridMap*)pGrid, r, dx);
	}

	void FilterGridMotionRight(const Rect& r, int* dx) const {
		const GridMap* pGrid = &grid;
		GridUtilities::FilterGridMotionRight((GridMap*)pGrid, r, dx);
	}


public:
	void FilterGridMotion(const Rect& r, int* dx, int* dy) const {
		const GridMap* pGrid = &grid;
		GridUtilities::FilterGridMotion((GridMap*)pGrid, r, dx, dy);
	}

	bool IsOnSolidGround(const Rect& r) const { // will need later for gravity
		int dy = 1; // down 1 pixel
		FilterGridMotionDown(r, &dy);
		return dy == 0; // if true IS attached to solid ground
	}

	GridMap* GetBuffer(void) {
		return &grid; //compile error, to see
	}

	const GridMap& GetBuffer(void) const {
		return grid; //compile error, to see
	}

	GridLayer() {
		Allocate();
	}
};

#endif