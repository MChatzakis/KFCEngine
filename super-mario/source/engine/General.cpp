#include "./General.h"

Res res;
Bitmap dpyBuffer = nullptr;
Point viewPosCached{ -1, -1 };
Dim dpyX = 0, dpyY = 0;

double Point::pointDistance(Point p1, Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

bool Point::onSegment(Point p, Point q, Point r)
{
	int maxX, minX, maxY, minY;
	if (p.x <= r.x) {
		maxX = r.x;
		minX = p.x;
	}
	else
	{
		maxX = p.x;
		minX = r.x;
	}

	if (p.y <= r.y) {
		maxY = r.y;
		minY = p.y;
	}
	else
	{
		maxY = p.y;
		minY = r.y;
	}

	if (q.x <= maxX && q.x >= minX && q.y <= maxY && q.y >= minY)
		return true;

	return false;
}

int Point::orientation(Point p, Point q, Point r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0; // collinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool Point::doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are collinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

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

	ALLEGRO_COLOR color = ColorToAllegroColor(c);

	al_clear_to_color(color);
	//al_clear_to_color(al_map_rgb(color.r, color.g, color.b));
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

	//ALLEGRO_BITMAP* currTarget = al_get_target_bitmap();

	//al_set_target_bitmap((ALLEGRO_BITMAP*)dest);
	//al_draw_bitmap_region((ALLEGRO_BITMAP*)tiles, CustomGetCol(tile) * TILE_WIDTH, CustomGetRow(tile) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, x, y, 0);

	al_set_target_bitmap((ALLEGRO_BITMAP*)dest);
	al_draw_bitmap_region((ALLEGRO_BITMAP*)src, from.x, from.y, from.w, from.h, to.x, to.y, 0);

	//al_set_target_bitmap(currTarget);
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

Color COLOR_KEY = 0;
void SetColorKey(Color c) {
	COLOR_KEY = c;
}

Color GetColorKey(void) {
	return COLOR_KEY;
}

Dim MaskedBlit(Bitmap src, const Rect& from, Bitmap dest, const Point& to) {
	ALLEGRO_COLOR mask;
	Color c = GetColorKey(); //must be set first

	mask = ColorToAllegroColor(c);

	al_convert_mask_to_alpha((ALLEGRO_BITMAP*)src, mask);
	BitmapBlit(src, from, dest, to);

	return 0;
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
	Convert Color to ALLEGRO_COLOR
*/
ALLEGRO_COLOR ColorToAllegroColor(Color c) { //or allegro color*?
	ALLEGRO_COLOR al_color;
	RGB color;
	Alpha a;
	PixelMemory pixel = (PixelMemory)&c;

	ReadPixelColor32(pixel, &color, &a);
	al_color.r = color.r;
	al_color.g = color.g;
	al_color.b = color.b;
	al_color.a = a;

	return al_color;
}

/*
	Write Pixel color mappings
*/
void WritePixelColor8(PixelMemory pixel, RGBValue color) {
	*pixel = color;
}

void WritePixelColor8(PixelMemory pixel, const RGB& color) { //why reference
	*pixel = Make8(color.r, color.g, color.b);
}

void WritePixelColor16(PixelMemory pixel, const RGB& color) {
	*pixel = Make16(color.r, color.g, color.b); //possible loss of information because color is uint but *pixel is uchar
}

void WritePixelColor24(PixelMemory pixel, const RGB& color) {
	*pixel = Make24(color.r, color.g, color.b);
}

void WritePixelColor32(PixelMemory pixel, const RGB& color, Alpha a) {
	*pixel = Make32(color.r, color.g, color.b, a);
}


/*
	Read Pixel color mappings
*/
//egw tha tou evaza idio signature me tis apo katw
void ReadPixelColor8(PixelMemory pixel, RGBValue* color) {
	*color = *pixel;
}

void ReadPixelColor8(PixelMemory pixel, RGB* color) {
	color->r = GetRedRGB8(pixel);
	color->g = GetGreenRGB8(pixel);
	color->b = GetBlueRGB8(pixel);
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

bool operator==(const Rect& l, const Rect& r) {
	return (l.x == r.x && l.y == r.y && l.w == r.w && l.h == r.h);
}

/*
	Sync mappings
*/
void Vsync(void) {
	al_flip_display();
}

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