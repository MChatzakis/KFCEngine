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

#define MARIO_CONF_PATH "resources/config/marioConf.json"
#define KOOPA_CONF_PATH "resources/config/koopaConf.json"
#define GOOMBA_CONF_PATH "resources/config/goombaConf.json"

#define SCROLLABLE_TILE_COL 212
#define WIN_TILE_DX 3150

#define FONT_PATH "resources/fonts/SuperMario256.ttf"
#define FONT_SIZE 30

#define DEATH_SCREEN_PATH "resources/screens/deathScreen.png"
#define STARTING_SCREEN_PATH "resources/screens/startingScreen.png"
#define WIN_SCREEN_PATH "resources/screens/winScreen.png"

#define FALL_COORDINATES_LIST {Rect(1104, 432, 1135-1104, 479-432), Rect(1376, 432, 1423-1376, 479-432), Rect(2448, 432, 2479-2448, 479-432)}

/* Global Stuff */
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

int SHOW_GRID_DEBUG = 0;
int TOGGLE_FILLED_RECT = 0;

/*ALLEGRO related*/
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_KEYBOARD_STATE keyboard_state;
ALLEGRO_MOUSE_STATE mouse_state;

Game* game;
TileLayer* gameMap;
Clipper clipper;
Bitmap tileSet;

int GAME_HAS_ENDED = 0;

#endif _GAMEVARS_H_