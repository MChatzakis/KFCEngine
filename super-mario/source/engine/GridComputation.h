#ifndef _GRIDCOMPUTATION_H_
#define _GRIDCOMPUTATION_H_

#include <iostream>

#include "./GridLayer.h"
#include "./TileLayer.h"

class GridComputation {
public:
	static void ComputeTileGridBlocks1(TileLayer* layer);
	static GridIndex* GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid);
	static void SetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid, GridIndex flags);
	static void DisplayGrid(Bitmap dest, const Rect& viewWin, GridIndex* grid, Dim tileCols);
};

//ok
void GridComputation::ComputeTileGridBlocks1(TileLayer* layer) {
	GridLayer* gridLayer = layer->GetGrid();
	GridIndex* grid = gridLayer->GetBuffer();
	for (auto row = 0; row < layer->GetTotalRows(); ++row) //change
		for (auto col = 0; col < layer->GetTotalColumns(); ++col) {
			memset(grid, gridLayer->IsTileIndexAssumedEmpty(layer->GetTile(col, row)) ? GRID_EMPTY_TILE : GRID_SOLID_TILE, GRID_ELEMENTS_PER_TILE);
			grid += GRID_ELEMENTS_PER_TILE;
		}
}

//ok
GridIndex* GridComputation::GetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid) {
	return grid + (rowTile * tileCols + colTile) * GRID_BLOCK_SIZEOF;

}

//ok
void GridComputation::SetGridTileBlock(Dim colTile, Dim rowTile, Dim tileCols, GridIndex* grid, GridIndex flags) {
	memset(GetGridTileBlock(colTile, rowTile, tileCols, grid), flags, GRID_BLOCK_SIZEOF);
}

//ok
void GridComputation::DisplayGrid(Bitmap dest, const Rect& viewWin, GridIndex* grid, Dim tileCols) {
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

#endif _GRIDCOMPUTATION_H_