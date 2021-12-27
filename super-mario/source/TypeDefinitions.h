#ifndef _TYPEDEFINITIONS_H_
#define _TYPEDEFINITIONS_H_

#include <allegro5/allegro.h>

#define TILESET_WIDTH 26 // row = 26 tiles .. better in json
#define TILESET_HEIGHT 24 // col = 24 tiles
#define TILE_WIDTH 16 //pixels
#define TILE_HEIGHT 16
#define MAX_WIDTH 640 //pixels or 40 tiles
#define MAX_HEIGHT 480 //pixels or 30 tiles
#define TILEMAP_WIDTH 228
#define TILEMAP_HEIGHT 30

#define ROW_MASK 0x0F
#define COL_MASK 0xF0
#define COL_SHIFT 4

typedef unsigned char byte;
typedef unsigned short Dim;
typedef unsigned short Index; // [MSB X][LSB Y]

#define TILEX_MASK 0xFF00
#define TILEX_SHIFT 8
#define TILEY_MASK 0x00FF

struct Rect {
	int x, y, w, h;
	Rect(int _x, int _y, int _w, int _h) : x{ _x }, y{ _y }, w{ _w }, h{ _h } {};
	Rect() { x = y = w = h = 0; };
};

struct Point {
	int x, y;
	Point(int _x, int _y) : x{ _x }, y{ _y }{};
	Point() { x = y = 0; };
};

enum BitDepth { bits8 = 1, bits16, bits24, bits32 };

struct Res {
	Dim rw, rh;
	BitDepth depth;
	Res(Dim _w, Dim _h, BitDepth _depth) : rw{ _w }, rh{ _h }, depth{_depth}{};
	Res() { rw = rh = 0; depth = bits32; };
};

Res res;

bool Open(Dim rw, Dim rh, BitDepth depth) {
	res = Res();
	res.rw = rw;
	res.rh = rh;
	res.depth = depth;

	return true;
}

void Close(void) {
}

Dim GetResWidth(void) {
	return res.rw;
}

Dim GetResHeight(void) {
	return res.rh;
}

/*BitDepth GetDepth(void) {
	return res.depth;
}*/

BitDepth GetDepth(void) {
	return bits32;
}

typedef unsigned int Color;
typedef unsigned char RGBValue;
typedef unsigned char Alpha;

struct RGB { RGBValue r, g, b; };
struct RGBA : public RGB { RGBValue a; };

typedef RGB Palette[256];

typedef void* Bitmap;
typedef unsigned char* PixelMemory;

#define MUL_TILE_WIDTH(i) ((i)<<4)
#define MUL_TILE_HEIGHT(i)((i)<<4)
#define DIV_TILE_WIDTH(i) ((i)>>4)
#define DIV_TILE_HEIGHT(i)((i)>>4)
#define MOD_TILE_WIDTH(i) ((i)&15)
#define MOD_TILE_HEIGHT(i)((i)&15)

typedef Index TileMap[TILEMAP_HEIGHT][TILEMAP_WIDTH];
static TileMap map; // example of a global static map
//static TileMap map_sky;

Bitmap dpyBuffer = nullptr;
Point viewPosCached{ -1, -1 };
Dim dpyX = 0, dpyY = 0;

typedef unsigned char* PixelMemory;
//...............................................
void SetPalette(RGB* palette); //set colors

Color Make8(RGBValue r, RGBValue g, RGBValue b) {
	Color res;
	RGBValue red = r & 0x07; // 3 bits -> 111
	RGBValue green = g & 0x03; // 2 bits -> 11
	RGBValue blue = b & 0x07; // 3 bits -> 111
	res = (red << 5) + (green << 3) + blue;
	return res;
}//8 bits color, isws al_map / al_unmap_rgb
Color Make16(RGBValue r, RGBValue g, RGBValue b); //16 bits color
Color Make24(RGBValue r, RGBValue g, RGBValue b); //24 bits color
Color Make32(RGBValue r, RGBValue g, RGBValue b, Alpha alpha = 0); //24 bits color and 8 bits alpha

Bitmap BitmapLoad(const char* path) {
	return al_load_bitmap(path);
}

Bitmap BitmapCreate(Dim w, Dim h) {
	return al_create_bitmap(w, h);
} 

Bitmap BitmapCopy(Bitmap bmp) {
	return al_clone_bitmap((ALLEGRO_BITMAP*)bmp);
}

Bitmap BitmapClear(Bitmap bmp, Color c) {
	ALLEGRO_BITMAP* currTarget = al_get_target_bitmap();
	al_set_target_bitmap((ALLEGRO_BITMAP*)bmp);

	int r = (c >> 16) & 0xFF; //na to kanoume function
	int g = (c >> 8) & 0xFF;
	int b = (c >> 0) & 0xFF;

	al_clear_to_color(al_map_rgb(r, g, b));
	al_set_target_bitmap(currTarget);

	return bmp;
}

void BitmapDestroy(Bitmap bmp) {
	al_destroy_bitmap((ALLEGRO_BITMAP*)bmp);
}

Bitmap BitmapGetScreen(ALLEGRO_DISPLAY* display) { //changed the argument
	return al_get_backbuffer(display);
}

Dim BitmapGetWidth(Bitmap bmp) {
	return al_get_bitmap_width((ALLEGRO_BITMAP*)bmp);
}

Dim BitmapGetHeight(Bitmap bmp) {
	return al_get_bitmap_height((ALLEGRO_BITMAP*)bmp);
}

void BitmapBlit(Bitmap src, const Rect& from, Bitmap dest, const Point& to) {

	ALLEGRO_BITMAP* currTarget = al_get_target_bitmap();

	al_set_target_bitmap((ALLEGRO_BITMAP*)dest);
	al_draw_bitmap_region((ALLEGRO_BITMAP*)src, from.x, from.y, from.w, from.h, to.x, to.y, 0);
	al_set_target_bitmap(currTarget);
}

bool BitmapLock(Bitmap bmp) {
	if (!al_lock_bitmap((ALLEGRO_BITMAP*)bmp, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE))
		return false;
	return true;
}

void BitmapUnlock(Bitmap bmp) {
	al_unlock_bitmap((ALLEGRO_BITMAP*)bmp);
}

PixelMemory BitmapGetMemory(Bitmap bmp) {
	auto mem = al_lock_bitmap((ALLEGRO_BITMAP*)bmp, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	std::cout << "----------" << mem->pixel_size << std::endl;
	return (PixelMemory)mem->data;
}

void WritePixelColor8(PixelMemory, RGBValue); //draw pixel with color
void WritePixelColor16(PixelMemory, const RGB&);
void WritePixelColor24(PixelMemory, const RGB&);
void WritePixelColor32(PixelMemory, const RGB&, Alpha a);
void ReadPixelColor8(PixelMemory, RGBValue*); //read pixel color
void ReadPixelColor16(PixelMemory, RGB*);
void ReadPixelColor24(PixelMemory, RGB*);
void ReadPixelColor32(PixelMemory, RGB*, Alpha*);
//Lecture 6 mexri kai selida 25

int BitmapGetLineOffset(Bitmap bmp) {
	return GetDepth() * al_get_bitmap_width((ALLEGRO_BITMAP*)bmp);
}

//................................................
using BitmapAccessFunctor = std::function<void(PixelMemory*)>;
void BitmapAccessPixels(Bitmap bmp, const BitmapAccessFunctor& f) {
	auto result = BitmapLock(bmp);
	assert(result);
	auto mem = BitmapGetMemory(bmp);
	auto offset = BitmapGetLineOffset(bmp);
	for (auto y = BitmapGetHeight(bmp); y--; ) {
		auto buff = mem;
		for (auto x = BitmapGetWidth(bmp); x--; ) {
			f((PixelMemory*)buff);
			buff += GetDepth();
		}
		mem += offset;
	}

	BitmapUnlock(bmp);
}

#endif
