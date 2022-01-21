#include "./TileLayer.h"

//SCROLL UTILITIES

void ScrollUtilities::TileTerrainDisplay(TileMap* map, Bitmap dest, const Rect& viewWin, /*const Rect& displayArea,*/ Bitmap tiles) {
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

int ScrollUtilities::GetMapPixelWidth(void) {
	return TILEMAP_WIDTH * TILE_WIDTH; //change on define
}

int ScrollUtilities::GetMapPixelHeight(void) {
	return TILEMAP_HEIGHT * TILE_HEIGHT;
}

void ScrollUtilities::Scroll(Rect* viewWin, int dx, int dy) {
	viewWin->x += dx; viewWin->y += dy;
}

bool ScrollUtilities::CanScrollHoriz(const Rect& viewWin, int dx) {
	return viewWin.x >= -dx &&
		(viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
}

bool ScrollUtilities::CanScrollVert(const Rect& viewWin, int dy) {
	return viewWin.y >= -dy &&
		(viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
}

void ScrollUtilities::FilterScrollDistance(int viewStartCoord, /* x or y*/int viewSize, /* w or h*/int* d, /* dx or dy*/ 	int maxMapSize /* w or h*/) {
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

void ScrollUtilities::FilterScroll(const Rect& viewWin, int* dx, int* dy) {
	FilterScrollDistance(viewWin.x, viewWin.w, dx, GetMapPixelWidth());
	FilterScrollDistance(viewWin.y, viewWin.h, dy, GetMapPixelHeight());
}

void ScrollUtilities::ScrollWithBoundsCheck(Rect* viewWin, int dx, int dy) {
	FilterScroll(*viewWin, &dx, &dy);
	Scroll(viewWin, dx, dy);
}

//TILE LAYER
//ok
Dim TileLayer::GetTotalRows() {
	return totalRows;
}

//ok
Dim TileLayer::GetTotalColumns() {
	return totalColumns;
}

//ok
GridLayer* TileLayer::GetGrid() {
	return grid;
}

//ok
Index* TileLayer::GetTileMap() {
	return map;
}

//ok
void TileLayer::SetTile(Dim col, Dim row, Index index) {
	map[row * totalColumns + col] = index;
}

//ok
Index TileLayer::GetTile(Dim col, Dim row) const
{
	return map[row * totalColumns + col];
}

//ok
const Point TileLayer::Pick(Dim x, Dim y) const {
	return { DIV_TILE_WIDTH(x + viewWin.x),	DIV_TILE_HEIGHT(y + viewWin.y) };
}

//ok
const Rect& TileLayer::GetViewWindow(void) const {
	return viewWin;
}

//ok
void TileLayer::SetViewWindow(const Rect& r)
{
	viewWin = r;
	dpyChanged = true;
}

//ok
void TileLayer::Display(Bitmap dest/*, const Rect& displayArea*/) {
	//al_clear_to_color(al_map_rgb(0, 0, 0)); //clear everything
	//ScrollUtilities::TileTerrainDisplay(*map, dest, viewWin, tileSet);
	if (viewPosCached.x != viewWin.x || viewPosCached.y != viewWin.y) {
	//if (true) {
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
				TileUtilities::PutTile(/*dpyBuffer*/ dest, MUL_TILE_WIDTH(col - startCol), MUL_TILE_HEIGHT(row - startRow), tileSet, GetTile(col, row));
	}
}

//ok
Bitmap TileLayer::GetBitmap(void) const {
	return dpyBuffer;
}

//ok
int TileLayer::GetPixelWidth(void) const {
	return viewWin.w;
}

//ok
int TileLayer::GetPixelHeight(void) const {
	return viewWin.h;
}

//ok
unsigned TileLayer::GetTileWidth(void) const {
	return DIV_TILE_WIDTH(viewWin.w);
}

//ok
unsigned TileLayer::GetTileHeight(void) const {
	return DIV_TILE_HEIGHT(viewWin.h);
}

//ok
void TileLayer::Scroll(float dx, float dy) {
	viewWin.x += dx; viewWin.y += dy;
}

//ok
int TileLayer::GetMapPixelWidth() {
	return totalColumns * TILE_WIDTH;
}

//ok
int TileLayer::GetMapPixelHeight() {
	return totalRows * TILE_HEIGHT;
}

//ok
bool TileLayer::CanScrollHoriz(float dx) {
	return viewWin.x >= -dx && (viewWin.x + viewWin.w + dx) <= GetMapPixelWidth();
}

//ok
bool TileLayer::CanScrollVert(float dy) {
	return viewWin.y >= -dy && (viewWin.y + viewWin.h + dy) <= GetMapPixelHeight();
}

//ok
void TileLayer::FilterScrollDistance(int viewStartCoord, /* x or y*/int viewSize, /* w or h*/int* d, /* dx or dy*/ int maxMapSize /* w or h*/) {
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

//ok
void TileLayer::FilterScroll(int* dx, int* dy) {
	FilterScrollDistance(viewWin.x, viewWin.w, dx, GetMapPixelWidth());
	FilterScrollDistance(viewWin.y, viewWin.h, dy, GetMapPixelHeight());
}

//ok
void TileLayer::ScrollWithBoundsCheck(int dx, int dy) {
	FilterScroll(&dx, &dy);
	Scroll(dx, dy);
}

//ok
auto TileLayer::ToString(void) const -> const std::string {
	return std::string("To String is not implemented yet!");
}

//?
bool TileLayer::FromString(const std::string&) {
	assert(0); //???
	return false;
}

//ok
void TileLayer::Save(const std::string& path) const
{
	fclose(WriteText(fopen(path.c_str(), "wt")));
}

//?
bool TileLayer::Load(const std::string& path) {
	assert(0);
	return false;
}

//ok
FILE* TileLayer::WriteText(FILE* fp) const
{
	fprintf(fp, "%s", ToString().c_str()); return fp;
}

//ok
bool TileLayer::ReadText(const char* path) {
	Index index;
	Dim row = 0, column = 0;

	std::string line;
	std::ifstream fp(path);

	if (!fp.is_open()) return false;

	while (std::getline(fp, line)) {
		char* values = strtok((char*)line.c_str(), ",");
		while (values != NULL)
		{
			long currNum = strtol(values, NULL, 0);
			if (currNum >= 0) {
				index = (Index)currNum;
				SetTile(column, row, index);
			}

			column++;
			values = strtok(NULL, ",");
		}
		row++;
		column = 0;
	}
	fp.close();
	return true;
}

//ok
TileLayer::TileLayer(Dim _rows, Dim _cols, const Bitmap& _tileSet, const Rect& _viewWin) {
	totalRows = _rows;
	totalColumns = _cols;
	tileSet = _tileSet;
	viewWin = _viewWin;
	Allocate();

}

//ok, uncomment
TileLayer::~TileLayer() {
	/*delete map;
	delete grid;

	BitmapDestroy(dpyBuffer);
	BitmapDestroy(tileSet); //dont destroy here, it is called in main file*/
}

void TileLayer::Allocate(void) {
	map = new Index[totalRows * totalColumns];
	grid = new GridLayer(totalRows * GRID_BLOCK_ROWS, totalColumns * GRID_BLOCK_COLUMNS);
	dpyBuffer = BitmapCreate(GetResWidth() + 2 * TILE_WIDTH, GetResHeight() + 2 * TILE_HEIGHT);
}