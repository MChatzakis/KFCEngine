#include "./TileUtilities.h"

int EMPTY_INDICES[TOTAL_EMPTY_INDICES] = { 10,11,12,61,62,63,87,88,89/*plants*/,344/*sky*/,472,473,474,498, 499, 500,/*clouds 16 ews edw*/549 };

byte TileUtilities::MakeIndex(byte row, byte col)
{
	return (col << COL_SHIFT) | row;
	//episis de mas kanei to byte san type
	//return row * TILESET_WIDTH + col;
}

byte TileUtilities::GetCol(byte index)
{
	return index >> COL_SHIFT;
	//return index % TILESET_WIDTH;
}

byte TileUtilities::GetRow(byte index)
{
	return index & ROW_MASK;
	//return index / TILESET_WIDTH;
}

Dim TileUtilities::TileX(byte index)
{
	return GetCol(index) * TILESET_WIDTH;
}

Dim TileUtilities::TileY(byte index)
{
	return GetRow(index) * TILESET_HEIGHT;
}

Dim TileUtilities::TileX2(byte index)
{
	return MUL_TILE_WIDTH(GetCol(index));
}

Dim TileUtilities::TileY2(byte index)
{
	return MUL_TILE_HEIGHT(GetRow(index));
}

Index TileUtilities::MakeIndex2(byte row, byte col)
{
	return (MUL_TILE_WIDTH(col) << TILEX_SHIFT) | MUL_TILE_HEIGHT(row);
}

Dim TileUtilities::TileX3(Index index) {
	return index >> TILEX_SHIFT;
}

Dim TileUtilities::TileY3(Index index) {
	return index & TILEY_MASK;
}

Index TileUtilities::CustomMakeIndex(Dim row, Dim col)
{
	return (Index)row * TILESET_WIDTH + col;
}

Dim TileUtilities::CustomGetCol(Index index)
{
	return index % TILESET_WIDTH;
}

Dim TileUtilities::CustomGetRow(Index index)
{
	return index / TILESET_WIDTH;
}

void TileUtilities::PutTile(Bitmap dest, Dim x, Dim y, Bitmap tiles, Index tile) {
	//BitmapBlit(tiles, Rect{ TileX3(tile), TileY3(tile), TILE_WIDTH, TILE_HEIGHT }, dest, Point{ x, y });
	// POIO EINAI TO TARGET DEST GAMW TO SPITAKI?
	//al_draw_bitmap_region((ALLEGRO_BITMAP*)tiles, TileX3(tile) * TILE_WIDTH, TileY3(tile), TILE_WIDTH * TILE_HEIGHT, TILE_HEIGHT, x, y, 0);

	//al_set_target_bitmap((ALLEGRO_BITMAP*)dest);
	//al_draw_bitmap_region((ALLEGRO_BITMAP*)tiles, CustomGetCol(tile) * TILE_WIDTH, CustomGetRow(tile) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, x, y, 0);

	BitmapBlit(tiles, Rect(CustomGetCol(tile) * TILE_WIDTH, CustomGetRow(tile) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT), dest, Point(x, y));
}

//startDx -> dx in pixels from the start of the bitmap tile. endDx -> dx in pixels from the start of the bitmap tile.
//it helps in order to not display all the tile
void TileUtilities::PutTile(Bitmap dest, Dim x, Dim y, Bitmap tiles, Index tile, Dim startDx, Dim startDy, Dim tileWidth, Dim tileHeight) {
	BitmapBlit(tiles, Rect(CustomGetCol(tile) * TILE_WIDTH + startDx, CustomGetRow(tile) * TILE_HEIGHT + startDy, tileWidth, tileHeight), dest, Point(x, y));
}

void TileUtilities::SetTile(TileMap* m, Dim col, Dim row, Index index)
{
	(*m)[row][col] = index;
}

Index TileUtilities::GetTile(const TileMap* m, Dim col, Dim row)
{
	return (*m)[row][col];
}

void TileUtilities::WriteBinMap(const TileMap* m, FILE* fp)
{
	fwrite(m, sizeof(TileMap), 1, fp);
} // simplistic...

bool TileUtilities::ReadBinMap(TileMap* m, FILE* fp)
{ // binary formatted read, like descent parsing
	assert(false);
	return false;
}

void TileUtilities::WriteTextMap(const TileMap* m, const char* filename)
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
bool TileUtilities::ReadTextMap(TileMap* m, const char* filename) {
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

void TileUtilities::printTileMap_DEBUG(TileMap* m) {


	for (int i = 0; i < TILEMAP_HEIGHT; i++) {
		std::cout << "[" << i << "]: ";
		for (int j = 0; j < TILEMAP_WIDTH; j++) {
			std::cout << GetTile(m, j, i) << " ";
		}
		std::cout << "\n";
	}
}