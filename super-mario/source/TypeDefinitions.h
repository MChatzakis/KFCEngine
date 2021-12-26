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

bool Open(Dim rw, Dim rh, BitDepth depth); //open/create resolution
void Close(void); //close/delete resolution
Dim GetResWidth(void); //resolution width
Dim GetResHeight(void);//resolution height
BitDepth GetDepth(void); //pixel depth

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
static TileMap map_sky;

Bitmap dpyBuffer = nullptr;
Point viewPosCached{ -1, -1 };
Dim dpyX = 0, dpyY = 0;

typedef unsigned char* PixelMemory;
//...............................................
void SetPalette(RGB* palette); //set colors with the 4 below functions
Color Make8(RGBValue r, RGBValue g, RGBValue b); //8 bits color, isws al_map / al_unmap_rgb
Color Make16(RGBValue r, RGBValue g, RGBValue b); //16 bits color
Color Make24(RGBValue r, RGBValue g, RGBValue b); //24 bits color
Color Make32(RGBValue r, RGBValue g, RGBValue b, Alpha alpha = 0); //24 bits color and 8 bits alpha
Bitmap BitmapLoad(const std::string& path); //al_load_bitmap
Bitmap BitmapCreate(Dim w, Dim h); //al_create_bitmap
Bitmap BitmapCopy(Bitmap bmp);
Bitmap BitmapClear(Bitmap bmp, Color c); //al_clear_to_color
void BitmapDestroy(Bitmap bmp); //al_destroy_bitmap
Bitmap BitmapGetScreen(void); //al_get_backbuffer ? 
Dim BitmapGetWidth(Bitmap bmp); //al_get_bitmap_width
Dim BitmapGetHeight(Bitmap bmp); //al_get_bitmap_height
void BitmapBlit(
	Bitmap src, const Rect& from,
	Bitmap dest, const Point& to
); //al_draw_bitmap_region

bool BitmapLock(Bitmap); //al_lock_bitmap
void BitmapUnlock(Bitmap); //al_unlock_bitmap
PixelMemory BitmapGetMemory(Bitmap); //al_get_pixel?
int BitmapGetLineOffset(Bitmap); //width in bytes
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

BitDepth pixelDepth = bits32;

void SetDepth(BitDepth pDepth) {
	pixelDepth = pDepth;
}

BitDepth GetDepth(void) {
	return pixelDepth;
}
//................................................
using BitmapAccessFunctor = std::function<void(PixelMemory*)>;
void BitmapAccessPixels(Bitmap bmp, const BitmapAccessFunctor& f) {
	auto result = al_lock_bitmap((ALLEGRO_BITMAP *)bmp, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READWRITE);
	assert(result);
	auto mem = al_get_pixel((ALLEGRO_BITMAP*) &bmp,0,0); //not sure for this
	auto offset = BitmapGetLineOffset(bmp); 
	for (auto y = al_get_bitmap_height((ALLEGRO_BITMAP*)bmp); y--; ) {
		auto buff = mem;
		for (auto x = al_get_bitmap_width((ALLEGRO_BITMAP*)bmp); x--; ) {
			f((PixelMemory*)buff);
			buff += GetDepth();
		}
		mem += offset;
	}

	al_unlock_bitmap((ALLEGRO_BITMAP*)bmp);
}

#endif
