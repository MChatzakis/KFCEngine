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


#endif _GRIDCOMPUTATION_H_