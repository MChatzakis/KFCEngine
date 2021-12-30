#ifndef _ALLEGROMAPPINGS_H_
#define _ALLEGROMAPPINGS_H_

#include <iostream>
#include <functional>
#include <chrono>

#include <allegro5/allegro.h>

#include "../TypeDefinitions.h"

#define BitMask2Bits 0x03 //11
#define BitMask3Bits 0x07 //111 ktlp..
#define BitMask5Bits 0x1f
#define BitMask6Bits 0x3f
#define BitMask8Bits 0xFF
/*
TODOs:
1) Continue Completing the Allegro Mappings file
2) Implement all unimplented methods on {Tile,Grid .. }Layer class
3) See what is goind on with the map
*/

//extern int SCREEN_WIDTH;
//extern int SCREEN_HEIGHT;

/*
	Pallete init mappings
*/
void SetPalette(RGB* palette); //set colors //todo

/*
	Bitmap function mappings
*/
Bitmap BitmapLoad(const char* path);
Bitmap BitmapCreate(Dim w, Dim h);
Bitmap BitmapCopy(Bitmap bmp);
Bitmap BitmapClear(Bitmap bmp, Color c);
Bitmap BitmapGetScreen(ALLEGRO_DISPLAY* display);
Bitmap GetBackBuffer(void); //todo
Dim BitmapGetWidth(Bitmap bmp);
Dim BitmapGetHeight(Bitmap bmp);
Dim MaskedBlit(Bitmap src, const Rect& from, Bitmap dest, const Point& to); //todo
Rect& GetScreenRect(void); //todo
PixelMemory BitmapGetMemory(Bitmap bmp);
Color GetColorKey(void); //todo
Color GetBackgroundColor(void); //todo
void BitmapDestroy(Bitmap bmp);
void BitmapBlit(Bitmap src, const Rect& from, Bitmap dest, const Point& to);
void BitmapUnlock(Bitmap bmp);
void SetColorKey(Color c); //todo
void BitmapBlitTinted(Bitmap src, const Rect& from, Bitmap dest, const Point& to, Color modulation); //todo
void BitmapBlitTransparent(Bitmap src, const Rect& from, Bitmap dest, const Point& to, RGBValue alpha);
bool BitmapLock(Bitmap bmp);
int BitmapGetLineOffset(Bitmap bmp);

//---------------------------------
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

// function table approach 
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

#endif _ALLEGROMAPPINGS_H_