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

#define TILEMAP_WIDTH 228
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
static TileMap map;

Bitmap dpyBuffer = nullptr;
Point viewPosCached{ -1, -1 };
Dim dpyX = 0, dpyY = 0;

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
	Write Pixel color mappings
*/
void WritePixelColor8(PixelMemory, RGBValue); //draw pixel with color //todo
void WritePixelColor16(PixelMemory, const RGB&); //todo
void WritePixelColor24(PixelMemory, const RGB&); //todo
void WritePixelColor32(PixelMemory, const RGB&, Alpha a); //todo


/*
	Read Pixel color mappings
*/
void ReadPixelColor8(PixelMemory, RGBValue*); //read pixel color
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
/*void Render(Bitmap target); // do game rendering to target  //todo
void Vsync(void); // gfx lib function  //todo
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

/*
	Pallete init mappings
*/
void SetPalette(RGB* palette) {
	assert(0);
}

/*
	Bitmap function mappings
*/
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

Bitmap BitmapGetScreen() { //changed the argument
	return al_get_target_bitmap();
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
	//std::cout << "----------" << mem->pixel_size << std::endl;
	return (PixelMemory)mem->data;
}

int BitmapGetLineOffset(Bitmap bmp) {
	return GetDepth() * al_get_bitmap_width((ALLEGRO_BITMAP*)bmp);
}

Bitmap GetBackBuffer(ALLEGRO_DISPLAY* disp) {
	return al_get_backbuffer(disp);
}

Color GetBackgroundColor(void) {
	assert(0);
	return 0;
}

Rect& GetScreenRect(Dim w, Dim h) {
	return *(new Rect(0, 0, w, h));
}

Color COLOR_KEY;
void SetColorKey(Color c) {
	COLOR_KEY = c;
}

Color GetColorKey(void) {
	return COLOR_KEY;
}

Dim MaskedBlit(Bitmap src, const Rect& from, Bitmap dest, const Point& to) {
	ALLEGRO_COLOR mask;
	Color c = GetColorKey();

	int r = (c >> 16) & 0xFF; //na to kanoume function
	int g = (c >> 8) & 0xFF;
	int b = (c >> 0) & 0xFF;

	/*proswrina*/
	mask.r = r;
	mask.g = g;
	mask.b = b;

	al_convert_mask_to_alpha((ALLEGRO_BITMAP*)src, mask);
	BitmapBlit(src, from, dest, to);

	return 0; //??
}

void BitmapBlitTinted(Bitmap src, const Rect& from, Bitmap dest, const Point& to, Color modulation) {
	ALLEGRO_COLOR color = al_map_rgba_f(1, 0, 0, 1); //todo modulation
	ALLEGRO_BITMAP* currTarget = al_get_target_bitmap();

	al_set_target_bitmap((ALLEGRO_BITMAP*)dest);
	al_draw_tinted_bitmap_region((ALLEGRO_BITMAP*)src, color, from.x, from.y, from.w, from.h, to.x, to.y, 0);
	al_set_target_bitmap(currTarget);
}

// emulate transparent blending
void BitmapBlitTransparent(Bitmap src, const Rect& from, Bitmap dest, const Point& to, RGBValue alpha) {
	BitmapBlitTinted(src, from, dest, to, Make32(255, 255, 255, alpha));
}

/*
	Bitmap Access pixels mappings
*/
using BitmapAccessFunctor = std::function<void(PixelMemory*)>;
void BitmapAccessPixels(Bitmap bmp, const BitmapAccessFunctor& f) {
	//auto result = BitmapLock(bmp);
	//assert(result);
	auto mem = BitmapGetMemory(bmp); //doesnt need bitmap lock
	auto offset = BitmapGetLineOffset(bmp);
	for (auto y = BitmapGetHeight(bmp); y--; ) {
		auto buff = mem;
		for (auto x = BitmapGetWidth(bmp); x--; ) {
			//f((PixelMemory*)buff);
			f(&buff);
			buff += GetDepth();
		}
		mem += offset;
	}

	BitmapUnlock(bmp);
}

#define INVERTED_BYTE(b) (255 - (b))
#define TINTED_BYTE(b, f) ((b) * (f))
void InvertPixelColor32(PixelMemory pixel) {
	// assume RGBA order, low to high byte, alpha retained!
	pixel[0] = INVERTED_BYTE(pixel[0]);
	pixel[1] = INVERTED_BYTE(pixel[1]);
	pixel[2] = INVERTED_BYTE(pixel[2]);
}

void TintPixelColor32(PixelMemory pixel, float f) {
	pixel[0] = TINTED_BYTE(pixel[0], f);
	pixel[1] = TINTED_BYTE(pixel[1], f);
	pixel[2] = TINTED_BYTE(pixel[2], f);
}

void BitmapInvertPixels32(Bitmap bmp)
{
	assert(0);
	//BitmapAccessPixels(bmp, &InvertPixelColor32);
}

void BitmapTintPixels32(Bitmap bmp, float f) {
	assert(0);
	/*BitmapAccessPixels(
		bmp,
		[f](PixelMemory pixel) { TintPixelColor32(pixel, f); }
	);*/
}


/*
	Write Pixel color mappings
*/
void WritePixelColor8(PixelMemory, RGBValue) {
	assert(0);
} //draw pixel with color

void WritePixelColor16(PixelMemory, const RGB&) {
	assert(0);
}

void WritePixelColor24(PixelMemory, const RGB&) {
	assert(0);
}

void WritePixelColor32(PixelMemory, const RGB&, Alpha a) {
	assert(0);
}


/*
	Read Pixel color mappings
*/
//egw tha tou evaza idio signature me tis apo katw
void ReadPixelColor8(PixelMemory pixel, RGBValue* color) {
	*color = *pixel;
}

void ReadPixelColor16(PixelMemory pixel, RGB* color) {
	color->r = GetRedRGB16(pixel);
	color->g = GetGreenRGB16(pixel);
	color->b = GetBlueRGB16(pixel);
}

void ReadPixelColor24(PixelMemory pixel, RGB* color) {
	color->r = GetRedRGB24(pixel);
	color->g = GetGreenRGB24(pixel);
	color->b = GetBlueRGB24(pixel);
}

void ReadPixelColor32(PixelMemory pixel, RGB* color, Alpha* alpha) {
	color->r = GetRedRGBA(pixel);
	color->g = GetGreenRGBA(pixel);
	color->b = GetBlueRGBA(pixel);
	*alpha = GetAlphaRGBA(pixel);
}


/*
	Color Make mappings
*/
Color Make8(RGBValue r, RGBValue g, RGBValue b) {
	Color red = r, green = g, blue = b;
	red = (red & GetRedBitMaskRGB8()) << GetRedShiftRGB8();
	green = (green & GetGreenBitMaskRGB8()) << GetGreenShiftRGB8();
	blue = (blue & GetBlueBitMaskRGB8()) << GetBlueShiftRGB8();
	return red + green + blue;
}//8 bits color, isws al_map / al_unmap_rgb

Color Make16(RGBValue r, RGBValue g, RGBValue b) {
	Color red = r, green = g, blue = b;
	red = (red & GetRedBitMaskRGB16()) << GetRedShiftRGB16();
	green = (green & GetGreenBitMaskRGB16()) << GetGreenShiftRGB16();
	blue = (blue & GetBlueBitMaskRGB16()) << GetBlueShiftRGB16();
	return red + green + blue;
}//16 bits color

Color Make24(RGBValue r, RGBValue g, RGBValue b) {
	Color red = r, green = g, blue = b;
	red = (red & GetRedBitMaskRGB24()) << GetRedShiftRGB24();
	green = (green & GetGreenBitMaskRGB24()) << GetGreenShiftRGB24();
	blue = (blue & GetBlueBitMaskRGB24()) << GetBlueShiftRGB24();
	return red + green + blue;
}//24 bits color

Color Make32(RGBValue r, RGBValue g, RGBValue b, Alpha alpha) {
	Color red = r, green = g, blue = b, a = alpha;
	red = (red & GetRedBitMaskRGBA()) << GetRedShiftRGBA();
	green = (green & GetGreenBitMaskRGBA()) << GetGreenShiftRGBA();
	blue = (blue & GetBlueBitMaskRGBA()) << GetBlueShiftRGBA();
	a = (a & GetAlphaBitMaskRGBA()) << GetAlphaShiftRGBA();
	return red + green + blue + a;
}//24 bits color and 8 bits alpha


/*
	Shift bit mask mappings
*/
//For pixel size 4 bytes (Color 3 bytes + alpha)
unsigned GetRedShiftRGBA(void) {
	return 24;
}

unsigned GetRedBitMaskRGBA(void) {
	//return 0xFF000000; //11111111000000000000000000000000
	return BitMask8Bits;
}

unsigned GetGreenShiftRGBA(void) {
	return 16;
}

unsigned GetGreenBitMaskRGBA(void) {
	return BitMask8Bits;
}

unsigned GetBlueShiftRGBA(void) {
	return 8;
}

unsigned GetBlueBitMaskRGBA(void) {
	return BitMask8Bits;
}

unsigned GetAlphaShiftRGBA(void) {
	return 0;
}

unsigned GetAlphaBitMaskRGBA(void) {
	return BitMask8Bits;
}

// firstly mask to isolate the RGB component, then shift to get value
RGBValue GetRedRGBA(PixelMemory pixel) {
	Color c = *((Color*)pixel); //exoun mperdeytei ta pixelmemory kai pixelmemory*
	return (c >> GetRedShiftRGBA()) & GetRedBitMaskRGBA();
}

RGBValue GetGreenRGBA(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetGreenShiftRGBA()) & GetGreenBitMaskRGBA();
}

RGBValue GetBlueRGBA(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetBlueShiftRGBA()) & GetBlueBitMaskRGBA();
}

Alpha GetAlphaRGBA(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetAlphaShiftRGBA()) & GetAlphaBitMaskRGBA();
}

/*For 3 byte pixels*/
unsigned GetRedShiftRGB24(void) {
	return 16;
}

unsigned GetRedBitMaskRGB24(void) {
	return BitMask8Bits;
}

unsigned GetGreenShiftRGB24(void) {
	return 8;
}

unsigned GetGreenBitMaskRGB24(void) {
	return BitMask8Bits;
}

unsigned GetBlueShiftRGB24(void) {
	return 0;
}

unsigned GetBlueBitMaskRGB24(void) {
	return BitMask8Bits;
}

RGBValue GetRedRGB24(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetRedShiftRGB24()) & GetRedBitMaskRGB24();
}

RGBValue GetGreenRGB24(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetGreenShiftRGB24()) & GetGreenBitMaskRGB24();
}

RGBValue GetBlueRGB24(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetBlueShiftRGB24()) & GetBlueBitMaskRGB24();
}

//for 2 byte pixels
unsigned GetRedShiftRGB16(void) {
	return 11;
}

unsigned GetRedBitMaskRGB16(void) {
	return BitMask5Bits;
}

unsigned GetGreenShiftRGB16(void) {
	return 5;
}

unsigned GetGreenBitMaskRGB16(void) {
	return BitMask6Bits;
}

unsigned GetBlueShiftRGB16(void) {
	return 0;
}

unsigned GetBlueBitMaskRGB16(void) {
	return BitMask5Bits;
}

RGBValue GetRedRGB16(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetRedShiftRGB16()) & GetRedBitMaskRGB16();
}

RGBValue GetGreenRGB16(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetGreenShiftRGB16()) & GetGreenBitMaskRGB16();
}

RGBValue GetBlueRGB16(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetBlueShiftRGB16()) & GetBlueBitMaskRGB16();
}

//for 1 byte pixels
unsigned GetRedShiftRGB8(void) {
	return 5;
}

unsigned GetRedBitMaskRGB8(void) {
	return BitMask3Bits;
}

unsigned GetGreenShiftRGB8(void) {
	return 3;
}

unsigned GetGreenBitMaskRGB8(void) {
	return BitMask2Bits;
}

unsigned GetBlueShiftRGB8(void) {
	return 0;
}

unsigned GetBlueBitMaskRGB8(void) {
	return BitMask3Bits;
}

RGBValue GetRedRGB8(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetRedShiftRGB8()) & GetRedBitMaskRGB8();
}

RGBValue GetGreenRGB8(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetGreenShiftRGB8()) & GetGreenBitMaskRGB8();
}

RGBValue GetBlueRGB8(PixelMemory pixel) {
	Color c = *((Color*)pixel);
	return (c >> GetBlueShiftRGB8()) & GetBlueBitMaskRGB8();
}

/*
	Put Pixel mappings
*/
void PutPixel8(Bitmap b, Dim x, Dim y, Color c) {
	if (!BitmapLock(b))
		assert(false);
	WritePixelColor8(BitmapGetMemory(b) + y * (BitmapGetWidth(b) + BitmapGetLineOffset(b)) + x, (RGBValue)c);
	BitmapUnlock(b);
}

// function table approach
void PutPixel16(Bitmap b, Dim x, Dim y, Color c) {
	assert(false);
}

void PutPixel24(Bitmap b, Dim x, Dim y, Color c) {
	assert(false);
}

void PutPixel32(Bitmap b, Dim x, Dim y, Color c) {
	assert(false);
}

typedef void (*PutPixelFunc)(Bitmap b, Dim x, Dim y, Color c);

void PutPixel(Bitmap b, Dim x, Dim y, Color c)
{
	(*currPutPixel)(b, x, y, c);
}

void InstallPutPixel(void) // upon initialisation
{
	currPutPixel = putPixelFuncs[GetDepth() - 1];
}


/*
	Sync mappings
*/
/*extern void Render(Bitmap target);

// do game rendering to target
void Vsync(void) {
	// gfx lib function
	//al_wait_for_vsync()
	al_flip_display();
}
void Flush(void) {
	BitmapClear(GetBackBuffer(), GetBackgroundColor()); // optional
	Render(GetBackBuffer());
	Vsync();
	BitmapBlit(GetBackBuffer(), GetScreenRect(), BitmapGetScreen(), Point{ 0,0 });
}

//unsigned char frequencyTime; // e.g 14 msecs  75 Hz
//unsigned int timeToNextRendering = 0xffffffff;
uint64_t CurrTime(void) {
	uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return now;
} // timer in msecs

void Flush2(void) {
	if (timeToNextRendering >= CurrTime()) {
		Vsync(); // just done with refresh
		auto t = CurrTime();
		Render(GetBackBuffer());
		t = CurrTime() - t; // time required to render
		timeToNextRendering = CurrTime() + (frequencyTime - t);
	}
}
*/


#endif _GENERAL_H_