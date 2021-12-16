#include "../TypeDefinitions.h"
#include <cstdio>
#include <string>
#include <fstream>

byte MakeIndex(byte row, byte col)
{
	return (col << COL_SHIFT) | row;
	//episis de mas kanei to byte san type
	//return row * TILESET_WIDTH + col;
}
byte GetCol(byte index)
{
	return index >> COL_SHIFT;
	//return index % TILESET_WIDTH;
}
byte GetRow(byte index)
{
	return index & ROW_MASK;
	//return index / TILESET_WIDTH;
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


//Proswrina se sxolia giati den exoyme thn bitmapBlit
/*void PutTile(Bitmap dest, Dim x, Dim y, Bitmap tiles, Index tile) {
	BitmapBlit(
		tiles, Rect{ TileX3(tile), TileY3(tile), TILE_WIDTH, TILE_HEIGHT },
		dest, Point{ x, y }
	);
}*/




//typedef Index TileMap[MAX_WIDTH][MAX_HEIGHT];
typedef Index TileMap[TILEMAP_HEIGHT][TILEMAP_WIDTH];
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
*/
void WriteTextMap(const TileMap* m, const char* filename)
{ // custom write in text format
	std::ofstream fp(filename);
	if (!fp.is_open()) return;

	for (Dim row = 0; row < TILEMAP_HEIGHT; row++) {
		for (Dim column = 0; column < TILEMAP_WIDTH; column++) {
			//read number as a string from fp
			fp << (short)GetTile(m,column,row);
			if (column != TILEMAP_WIDTH - 1)
				fp << ",";
		}
		fp << "\n";
	}
	fp.close();
}

/*Nomizw oti afoy paei sto engine prepei na pairnei kai width, height san arguments*/
bool ReadTextMap(TileMap* m, const char* filename) {
	Index index;
	Dim row = 0, column = 0;
	std::string line;
	std::ifstream fp(filename);
	if (!fp.is_open()) return false;

	while (std::getline(fp, line)) {
		char* values = strtok((char*)line.c_str(), ",");
		while (values != NULL)
		{
			printf("%s ", values);
			index = (Index)strtol(values, NULL, 0); //de nomizw na xanei info
			SetTile(m, column, row, index);
			column++;
			values = strtok(NULL, ",");
		}
		row++;
		//std::cout <<  "Columns: " << column << std::endl;
		column = 0;
		printf("\n");
	}
	//std::cout << "Rows: " << row << std::endl;
	fp.close();
	return true;
}