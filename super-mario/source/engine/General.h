#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <functional>
#include <chrono>

#define TILESET_WIDTH 26 // row = 26 tiles .. better in json
#define TILESET_HEIGHT 24 // col = 24 tiles
#define TILE_WIDTH 16 //pixels
#define TILE_HEIGHT 16

//#define MAX_WIDTH 640 //pixels or 40 tiles
//#define MAX_HEIGHT 480 //pixels or 30 tiles

#define TILEMAP_WIDTH 252
#define TILEMAP_HEIGHT 30

#define MAX_WIDTH TILEMAP_WIDTH
#define MAX_HEIGHT TILEMAP_HEIGHT 


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

bool Open(Dim rw, Dim rh, BitDepth depth);

void Close(void);

Dim GetResWidth(void);

Dim GetResHeight(void);

/*BitDepth GetDepth(void) {
	return res.depth;
}*/

BitDepth GetDepth(void);

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
static TileMap map;

extern Point viewPosCached;
extern Dim dpyX, dpyY;

//--------------------------------- PART 2 ---------------------------------


typedef unsigned char* PixelMemory;

#define BitMask2Bits 0x03 //11
#define BitMask3Bits 0x07 //111 ktlp..
#define BitMask5Bits 0x1f
#define BitMask6Bits 0x3f
#define BitMask8Bits 0xFF

/*
	Pallete init mappings
*/
void SetPalette(RGB* palette);

/*
	Bitmap function mappings
*/
Bitmap BitmapLoad(const char* path);
Bitmap BitmapCreate(Dim w, Dim h);
Bitmap BitmapCopy(Bitmap bmp);
Bitmap BitmapClear(Bitmap bmp, Color c);
Bitmap BitmapGetScreen();
Bitmap GetBackBuffer(ALLEGRO_DISPLAY *disp);
Dim BitmapGetWidth(Bitmap bmp);
Dim BitmapGetHeight(Bitmap bmp);
Dim MaskedBlit(Bitmap src, const Rect& from, Bitmap dest, const Point& to);
Rect& GetScreenRect(Dim w, Dim h);
PixelMemory BitmapGetMemory(Bitmap bmp);
Color GetColorKey(void);
Color GetBackgroundColor(void);
void BitmapDestroy(Bitmap bmp);
void BitmapBlit(Bitmap src, const Rect& from, Bitmap dest, const Point& to);
void BitmapUnlock(Bitmap bmp);
void SetColorKey(Color c);
void BitmapBlitTinted(Bitmap src, const Rect& from, Bitmap dest, const Point& to, Color modulation); 
void BitmapBlitTransparent(Bitmap src, const Rect& from, Bitmap dest, const Point& to, RGBValue alpha);
bool BitmapLock(Bitmap bmp);
int BitmapGetLineOffset(Bitmap bmp);

/*
	Bitmap Access pixels mappings
*/
#define INVERTED_BYTE(b) (255 - (b))
#define TINTED_BYTE(b, f) ((b) * (f))

using BitmapAccessFunctor = std::function<void(PixelMemory*)>;

void BitmapAccessPixels(Bitmap bmp, const BitmapAccessFunctor& f);
void InvertPixelColor32(PixelMemory pixel);
void TintPixelColor32(PixelMemory pixel, float f);
void BitmapInvertPixels32(Bitmap bmp);
void BitmapTintPixels32(Bitmap bmp, float f);

/*
	Convert Color to ALLEGRO_COLOR
*/

ALLEGRO_COLOR ColorToAllegroColor(Color c);

/*
	Write Pixel color mappings
*/
void WritePixelColor8(PixelMemory, RGBValue); //draw pixel with color
void WritePixelColor8(PixelMemory, const RGB&);
void WritePixelColor16(PixelMemory, const RGB&);
void WritePixelColor24(PixelMemory, const RGB&);
void WritePixelColor32(PixelMemory, const RGB&, Alpha a);


/*
	Read Pixel color mappings
*/
void ReadPixelColor8(PixelMemory, RGBValue*); //read pixel color
void ReadPixelColor8(PixelMemory, RGB*);
void ReadPixelColor16(PixelMemory, RGB*);
void ReadPixelColor24(PixelMemory, RGB*);
void ReadPixelColor32(PixelMemory, RGB*, Alpha*);


/*
	Color Make mappings
*/
Color Make8(RGBValue r, RGBValue g, RGBValue b);
Color Make16(RGBValue r, RGBValue g, RGBValue b);
Color Make24(RGBValue r, RGBValue g, RGBValue b);
Color Make32(RGBValue r, RGBValue g, RGBValue b, Alpha alpha = 0);


/*
	Shift bit mask mappings
*/
//RGBA -> 32 bits for colors and alpha
unsigned GetRedShiftRGBA(void);
unsigned GetRedBitMaskRGBA(void);
unsigned GetGreenShiftRGBA(void);
unsigned GetGreenBitMaskRGBA(void);
unsigned GetBlueShiftRGBA(void);
unsigned GetBlueBitMaskRGBA(void);
unsigned GetAlphaShiftRGBA(void);
unsigned GetAlphaBitMaskRGBA(void);
RGBValue GetRedRGBA(PixelMemory pixel);
RGBValue GetGreenRGBA(PixelMemory pixel);
RGBValue GetBlueRGBA(PixelMemory pixel);
Alpha GetAlphaRGBA(PixelMemory pixel);

//RGB -> 24 bits for colors
unsigned GetRedShiftRGB24(void);
unsigned GetRedBitMaskRGB24(void);
unsigned GetGreenShiftRGB24(void);
unsigned GetGreenBitMaskRGB24(void);
unsigned GetBlueShiftRGB24(void);
unsigned GetBlueBitMaskRGB24(void);
RGBValue GetRedRGB24(PixelMemory pixel);
RGBValue GetGreenRGB24(PixelMemory pixel);
RGBValue GetBlueRGB24(PixelMemory pixel);

//RGB -> 16 bits for colors
unsigned GetRedShiftRGB16(void);
unsigned GetRedBitMaskRGB16(void);
unsigned GetGreenShiftRGB16(void);
unsigned GetGreenBitMaskRGB16(void);
unsigned GetBlueShiftRGB16(void);
unsigned GetBlueBitMaskRGB16(void);
RGBValue GetRedRGB16(PixelMemory pixel);
RGBValue GetGreenRGB16(PixelMemory pixel);
RGBValue GetBlueRGB16(PixelMemory pixel);

//RGB -> 8 bits for colors
unsigned GetRedShiftRGB8(void);
unsigned GetRedBitMaskRGB8(void);
unsigned GetGreenShiftRGB8(void);
unsigned GetGreenBitMaskRGB8(void);
unsigned GetBlueShiftRGB8(void);
unsigned GetBlueBitMaskRGB8(void);
RGBValue GetRedRGB8(PixelMemory pixel);
RGBValue GetGreenRGB8(PixelMemory pixel);
RGBValue GetBlueRGB8(PixelMemory pixel);

/*
	Put Pixel mappings
*/
void PutPixel8(Bitmap b, Dim x, Dim y, Color c); //ta alla giati einai static?
void PutPixel16(Bitmap b, Dim x, Dim y, Color c); //todo
void PutPixel24(Bitmap b, Dim x, Dim y, Color c); //todo
void PutPixel32(Bitmap b, Dim x, Dim y, Color c); //todo

typedef void (*PutPixelFunc)(Bitmap b, Dim x, Dim y, Color c); //todo

static PutPixelFunc putPixelFuncs[] = { PutPixel8, PutPixel16, PutPixel24, PutPixel32 };
static PutPixelFunc currPutPixel;

void PutPixel(Bitmap b, Dim x, Dim y, Color c);
void InstallPutPixel(void); // upon initialisation

/*
	Sync mappings
*/
void Vsync(void); // gfx lib function
/*void Render(Bitmap target); // do game rendering to target  //todo
void Flush(void);
void Flush2(void);

unsigned char frequencyTime; // e.g 14 msecs  75 Hz
unsigned int timeToNextRendering = 0xffffffff;

extern uint64_t CurrTime(void); // timer in msecs  //todo*/


/*
	***********************************************************************************************
												BODIES
	***********************************************************************************************
*/




#endif _GENERAL_H_