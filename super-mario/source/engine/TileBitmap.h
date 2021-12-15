#include "../TypeDefinitions.h"
#include <cstdio>

byte MakeIndex(byte row, byte col)
{
	return (col << COL_SHIFT) | row;
}
byte GetCol(byte index)
{
	return index >> COL_SHIFT;
}
byte GetRow(byte index)
{
	return index & ROW_MASK;
}

Dim TileX(byte index)
{
	return GetCol(index) * TILESET_WIDTH;
}
Dim TileY(byte index)
{
	return GetRow(index) * TILESET_HEIGHT;
}

#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i)((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i)((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i)((i)&15)
Dim TileX2(byte index)
{
	return MUL_TILE_WIDTH(GetCol(index));
}
Dim TileY2(byte index)
{
	return MUL_TILE_HEIGHT(GetRow(index));
}


Index MakeIndex2(byte row, byte col)
{
	return (MUL_TILE_WIDTH(col) << TILEX_SHIFT) | MUL_TILE_HEIGHT(row);
}
Dim TileX3(Index index) { return index >> TILEX_SHIFT; }
Dim TileY3(Index index) { return index & TILEY_MASK; }


void PutTile(Bitmap dest, Dim x, Dim y, Bitmap tiles, Index tile) {
	BitmapBlit(
		tiles, Rect{ TileX3(tile), TileY3(tile), TILE_WIDTH, TILE_HEIGHT },
		dest, Point{ x, y }
	);
}




typedef Index TileMap[MAX_WIDTH][MAX_HEIGHT];
static TileMap map; // example of a global static map
void SetTile(TileMap* m, Dim col, Dim row, Index index)
{
	(*m)[row][col] = index;
}
Index GetTile(const TileMap* m, Dim col, Dim row)
{
	return (*m)[row][col];
}

/*void WriteBinMap(const TileMap* m, FILE* fp)
{
	fwrite(m, sizeof(TileMap), 1, fp);
} // simplistic...
bool ReadBinMap(TileMap* m, FILE* fp)
{ // binary formatted read, like descent parsing
}
void WriteTextMap(const TileMap*, FILE* fp)
{ // custom write in text format
}*/

/*Nomizw oti afoy paei sto engine prepei na pairnei kai width, height san arguments*/
bool ReadTextMap(TileMap* m, FILE* fp)
{
	if (fp == NULL) return false;

	Index index;
	for (Dim row = 0; row < MAX_HEIGHT; row++) {
		for (Dim column = 0; column < MAX_WIDTH; column++) {
			//read number from fp
			fp >> index;
			SetTile(m, column, row, index);
		}
	}
	return true;
}