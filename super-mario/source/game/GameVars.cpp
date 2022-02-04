#include "GameVars.h"

int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

int SHOW_GRID_DEBUG = 0;
int TOGGLE_FILLED_RECT = 0;

/*ALLEGRO related*/
ALLEGRO_DISPLAY* display = nullptr;
ALLEGRO_EVENT_QUEUE* queue = nullptr;
ALLEGRO_KEYBOARD_STATE keyboard_state;
ALLEGRO_MOUSE_STATE mouse_state;

Game* game = nullptr;
TileLayer* gameMap = nullptr;
Clipper clipper;
Bitmap tileSet = nullptr;

int GAME_HAS_ENDED = 0;
bool LOCK_SCROLL = false;