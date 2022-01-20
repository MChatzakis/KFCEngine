#ifndef _GAMEVARS_H_
#define _GAMEVARS_H_

#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "../utils/Utils.h"

#include "../engine/General.h"
#include "../engine/Game.h"
#include "../engine/TileLayer.h"
#include "../engine/GridLayer.h"
#include "../engine/GridComputation.h"
#include "../engine/TileActions.h"

#define TILESET_PATH "resources/bitmaps/tileset.png"
#define SKY_PATH "resources/csv/level1-1_Sky.csv"
#define FLAG_PATH "resources/csv/level1-1_flag.csv"
#define BACKGROUND_PATH "resources/csv/level1-1_background.csv"
#define TERRAIN_PATH "resources/csv/level1-1_terain.csv"

#define MARIO_ANIMATIONS_PATH "resources/characters/mario.json"
#define KOOPA_ANIMATIONS_PATH "resources/characters/koopa.json"
#define GOOMBA_ANIMATIONS_PATH "resources/characters/goomba.json"

#define SCROLLABLE_TILE_COL 212


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

//Rect* viewWin;
//Rect* gridWin;

Game* game;
TileLayer* gameMap;
GridIndex* tmpGrid;
Bitmap tileSet;

//class Mario;
//Mario* mario;

#endif _GAMEVARS_H_