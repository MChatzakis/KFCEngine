#ifndef _GAMEVARS_H_
#define _GAMEVARS_H_

#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "../utils/Utils.h"

#include "../engine/General.h"
#include "../engine/Game.h"
#include "../engine/TileLayer.h"
#include "../engine/GridLayer.h"
#include "../engine/GridComputation.h"
#include "../engine/TileActions.h"
#include "../engine/Clipper.h"

#define TILESET_PATH "resources/bitmaps/tileset.png"
#define SKY_PATH "resources/csv/level1-1_Sky.csv"
#define FLAG_PATH "resources/csv/level1-1_flag.csv"
#define BACKGROUND_PATH "resources/csv/level1-1_background.csv"
#define TERRAIN_PATH "resources/csv/level1-1_terain.csv"

#define MARIO_ANIMATIONS_PATH "resources/characters/mario.json"
#define KOOPA_ANIMATIONS_PATH "resources/characters/koopa.json"
#define GOOMBA_ANIMATIONS_PATH "resources/characters/goomba.json"
#define POWERUP_ANIMATIONS_PATH "resources/characters/powerups.json"

#define MARIO_CONF_PATH "resources/config/marioConf.json"
#define KOOPA_CONF_PATH "resources/config/koopaConf.json"
#define GOOMBA_CONF_PATH "resources/config/goombaConf.json"
#define POWERUP_CONF_PATH "resources/config/powerupsConf.json"

#define SCROLLABLE_TILE_COL 212
#define WIN_TILE_DX 3150

#define FONT_PATH "resources/fonts/SuperMario256.ttf"
#define FONT_SIZE 30

#define DEATH_SCREEN_PATH "resources/screens/deathScreen.png"
#define STARTING_SCREEN_PATH "resources/screens/startingScreen.png"
#define WIN_SCREEN_PATH "resources/screens/winScreen.png"

#define FALL_COORDINATES_LIST {Rect(1104, 432, 1135-1104, 479-432), Rect(1376, 432, 1423-1376, 479-432), Rect(2448, 432, 2479-2448, 479-432)}

/* Global Stuff */
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int SHOW_GRID_DEBUG;
extern int TOGGLE_FILLED_RECT;

/*ALLEGRO related*/
extern ALLEGRO_DISPLAY* display;
extern ALLEGRO_EVENT_QUEUE* queue;
extern ALLEGRO_KEYBOARD_STATE keyboard_state;
extern ALLEGRO_MOUSE_STATE mouse_state;

extern Game* game;
extern TileLayer* gameMap;
extern Clipper clipper;
extern Bitmap tileSet;

extern int GAME_HAS_ENDED;

#endif _GAMEVARS_H_