#ifndef _TILEUTILITIES_H_
#define _TILEUTILITIES_H_ 

#include <iostream>
#include <functional>
#include <chrono>
#include <fstream>
#include <cstdio>
#include <string>

#include "./General.h"

#define TOTAL_EMPTY_INDICES  16
int EMPTY_INDICES[TOTAL_EMPTY_INDICES] = { 10,11,12,61,62,63,87,88,89/*plants*/,344/*sky*/,472,473,474,498, 499, 500,/*clouds*/ };

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

	static Dim TileX3(Index index) {
		return index >> TILEX_SHIFT;
	}

	static Dim TileY3(Index index) {
		return index & TILEY_MASK;
	}

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

	static void PutTile(Bitmap dest, Dim x, Dim y, Bitmap tiles, Index tile) {
		//BitmapBlit(tiles, Rect{ TileX3(tile), TileY3(tile), TILE_WIDTH, TILE_HEIGHT }, dest, Point{ x, y });
		// POIO EINAI TO TARGET DEST GAMW TO SPITAKI?
		//al_draw_bitmap_region((ALLEGRO_BITMAP*)tiles, TileX3(tile) * TILE_WIDTH, TileY3(tile), TILE_WIDTH * TILE_HEIGHT, TILE_HEIGHT, x, y, 0);
		
		//al_set_target_bitmap((ALLEGRO_BITMAP*)dest);
		//al_draw_bitmap_region((ALLEGRO_BITMAP*)tiles, CustomGetCol(tile) * TILE_WIDTH, CustomGetRow(tile) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, x, y, 0);

		BitmapBlit(tiles, Rect(CustomGetCol(tile) * TILE_WIDTH, CustomGetRow(tile) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT), dest, Point(x, y));
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

#endif _TILEUTILITIES_H_