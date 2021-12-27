#include "./AllegroMappings.h"

/*
	Pallete init mappings
*/
void SetPalette(RGB* palette); //set colors


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
	//std::cout << "----------" << mem->pixel_size << std::endl;
	return (PixelMemory)mem->data;
}

int BitmapGetLineOffset(Bitmap bmp) {
	return GetDepth() * al_get_bitmap_width((ALLEGRO_BITMAP*)bmp);
}

Bitmap GetBackBuffer(void); //todo

Color GetBackgroundColor(void); //todo

Rect& GetScreenRect(void); //todo

void SetColorKey(Color c);

Color GetColorKey(void);

Dim MaskedBlit(Bitmap src, const Rect& from, Bitmap dest, const Point& to);

void BitmapBlitTinted(Bitmap src, const Rect& from, Bitmap dest, const Point& to, Color modulation);

// emulate transparent blending
void BitmapBlitTransparent(Bitmap src, const Rect& from, Bitmap dest, const Point& to, RGBValue alpha) {
	BitmapBlitTinted(src, from, dest, to, Make32(255, 255, 255, alpha));
}


/*
	Bitmap Access pixels mappings
*/
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
	BitmapAccessPixels(bmp, &InvertPixelColor32);
}

void BitmapTintPixels32(Bitmap bmp, float f) {
	BitmapAccessPixels(
		bmp,
		[f](PixelMemory pixel) { TintPixelColor32(pixel, f); }
	);
}


/*
	Write Pixel color mappings
*/
void WritePixelColor8(PixelMemory, RGBValue); //draw pixel with color

void WritePixelColor16(PixelMemory, const RGB&);

void WritePixelColor24(PixelMemory, const RGB&);

void WritePixelColor32(PixelMemory, const RGB&, Alpha a);


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
	color->b = GetGreenRGB16(pixel);
}

void ReadPixelColor24(PixelMemory pixel, RGB* color) {
	color->r = GetRedRGB24(pixel);
	color->g = GetGreenRGB24(pixel);
	color->b = GetGreenRGB24(pixel);
}

void ReadPixelColor32(PixelMemory pixel, RGB* color, Alpha* alpha) {
	color->r = GetRedRGBA(pixel);
	color->g = GetGreenRGBA(pixel);
	color->b = GetGreenRGBA(pixel);
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

Color Make32(RGBValue r, RGBValue g, RGBValue b, Alpha alpha = 0) {
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
	Color c = *((Color*)pixel);
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
	WritePixelColor8(
		BitmapGetMemory(b) +
		y * (BitmapGetWidth(b) + BitmapGetLineOffset(b)) + x,
		(RGBValue)c
	);
	BitmapUnlock(b);
}

// function table approach
static void PutPixel16(Bitmap b, Dim x, Dim y, Color c);

static void PutPixel24(Bitmap b, Dim x, Dim y, Color c);

static void PutPixel32(Bitmap b, Dim x, Dim y, Color c);

typedef void (*PutPixelFunc)(Bitmap b, Dim x, Dim y, Color c);

static PutPixelFunc putPixelFuncs[] = {
PutPixel8, PutPixel16, PutPixel24, PutPixel32
};

static PutPixelFunc currPutPixel;

extern void PutPixel(Bitmap b, Dim x, Dim y, Color c)
{
	(*currPutPixel)(b, x, y, c);
}

extern void InstallPutPixel(void) // upon initialisation
{
	currPutPixel = putPixelFuncs[GetDepth() - 1];
}


/*
	Sync mappings
*/
extern void Render(Bitmap target); // do game rendering to target
extern void Vsync(void); // gfx lib function

void Flush(void) {
	BitmapClear(GetBackBuffer(), GetBackgroundColor()); // optional
	Render(GetBackBuffer);
	Vsync();
	BitmapBlit(
		GetBackBuffer(),
		GetScreenRect(),
		BitmapGetScreen(),
		Point{ 0,0 }
	);
}

unsigned char frequencyTime; // e.g 14 msecs  75 Hz
unsigned int timeToNextRendering = 0xffffffff;
extern uint64_t CurrTime(void); // timer in msecs

void Flush2(void) {
	if (timeToNextRendering >= CurrTime()) {
		Vsync(); // just done with refresh
		auto t = CurrTime();
		Render(GetBackBuffer());
		t = CurrTime() - t; // time required to render
		timeToNextRendering = CurrTime() + (frequencyTime - t);
	}
}
