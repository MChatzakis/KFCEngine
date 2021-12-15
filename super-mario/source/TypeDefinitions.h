#define TILESET_WIDTH 16 // row = 16 tiles
#define TILESET_HEIGHT 16 // col = 16 tiles
#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define ROW_MASK 0x0F
#define COL_MASK 0xF0
#define COL_SHIFT 4

typedef unsigned char byte;
typedef unsigned short Dim;

typedef unsigned short Index; // [MSB X][LSB Y]
#define TILEX_MASK 0xFF00
#define TILEX_SHIFT 8
#define TILEY_MASK 0x00FF

struct Rect { int x, y, w, h; }; 
struct Point { int x, y; };

enum BitDepth { bits8 = 1, bits16, bits24, bits32 };

bool Open(Dim rw, Dim rh, BitDepth depth);
void Close(void);
Dim GetResWidth(void);
Dim GetResHeight(void);
BitDepth GetDepth(void);

typedef unsigned int Color;
typedef unsigned char RGBValue;
typedef unsigned char Alpha;
struct RGB { RGBValue r, g, b; };
struct RGBA : public RGB { RGBValue a; };
typedef RGB Palette[256];

typedef void* Bitmap;

