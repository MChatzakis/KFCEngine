#ifndef _TILEUTILITIES_H_
#define _TILEUTILITIES_H_ 

#include <iostream>
#include <functional>
#include <chrono>
#include <fstream>
#include <cstdio>
#include <string>

#include "./General.h"

#define TOTAL_EMPTY_INDICES  17
extern int EMPTY_INDICES[TOTAL_EMPTY_INDICES];

//This class has all the functions related to tilemap modifications. Made for grouping. Everything is static.
class TileUtilities {
public:
	static byte MakeIndex(byte row, byte col);

	static byte GetCol(byte index);

	static byte GetRow(byte index);

	static Dim TileX(byte index);

	static Dim TileY(byte index);

	static Dim TileX2(byte index);

	static Dim TileY2(byte index);

	static Index MakeIndex2(byte row, byte col);

	static Dim TileX3(Index index);

	static Dim TileY3(Index index);

	static Index CustomMakeIndex(Dim row, Dim col);

	static Dim CustomGetCol(Index index);

	static Dim CustomGetRow(Index index);

	static void PutTile(Bitmap dest, Dim x, Dim y, Bitmap tiles, Index tile);
	static void PutTile(Bitmap dest, Dim x, Dim y, Bitmap tiles, Index tile, Dim startDx, Dim startDy, Dim tileWidth, Dim tileHeight);

	static void SetTile(TileMap* m, Dim col, Dim row, Index index);

	static Index GetTile(const TileMap* m, Dim col, Dim row);

	static void WriteBinMap(const TileMap* m, FILE* fp);

	static bool ReadBinMap(TileMap* m, FILE* fp);

	static void WriteTextMap(const TileMap* m, const char* filename);

	/*Nomizw oti afoy paei sto engine prepei na pairnei kai width, height san arguments*/
	static bool ReadTextMap(TileMap* m, const char* filename);

	static void printTileMap_DEBUG(TileMap* m);
};

#endif _TILEUTILITIES_H_