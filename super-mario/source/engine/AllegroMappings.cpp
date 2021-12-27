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
void ReadPixelColor8(PixelMemory, RGBValue*); //read pixel color

void ReadPixelColor16(PixelMemory, RGB*);

void ReadPixelColor24(PixelMemory, RGB*);

void ReadPixelColor32(PixelMemory, RGB*, Alpha*);


/*
	Color Make mappings
*/
Color Make8(RGBValue r, RGBValue g, RGBValue b) {
	Color red = (r & BitMask3Bits) << 5; // mask 3 bits -> 111
	Color green = (g & BitMask2Bits) << 3; // mask 2 bits -> 11
	Color blue = b & BitMask3Bits;
	return red + green + blue;
}//8 bits color, isws al_map / al_unmap_rgb

Color Make16(RGBValue r, RGBValue g, RGBValue b) {
	Color red = r, green = g, blue = b; //gia na mh xasoyme plhroforia kata to shifting
	red = (red & BitMask5Bits) << 11; // mask 5 bits -> 11111
	green = (green & BitMask6Bits) << 5; // mask 6 bits -> 111111
	blue = blue & BitMask5Bits;
	return red + green + blue;
}//16 bits color

Color Make24(RGBValue r, RGBValue g, RGBValue b) {
	Color red = r, green = g, blue = b;
	red = red << 16;
	green = green << 8;
	return red + green + blue;
}//24 bits color

Color Make32(RGBValue r, RGBValue g, RGBValue b, Alpha alpha = 0) {
	Color red = r, green = g, blue = b, a = alpha;
	red << 24;
	green << 16;
	blue << 8;
	return red + green + blue + a;
}//24 bits color and 8 bits alpha


/*
	Shift bit mask mappings
*/
//For pixel size 4 bytes
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
