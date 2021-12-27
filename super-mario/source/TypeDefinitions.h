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
	Res(Dim _w, Dim _h, BitDepth _depth) : rw{ _w }, rh{ _h }, depth{ _depth }{};
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


#endif
