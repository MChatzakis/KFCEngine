#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

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

Rect* viewWin;
Rect* gridWin;

Game* game;
TileLayer* gameMap;
GridIndex* tmpGrid;
Bitmap tileSet;


void Initialise() {
	nlohmann::json config = readJSON("resources/config/config.json");
	if (config == NULL) {
		std::cout << "Cannot open configuration file!" << std::endl;
		exit(-1);
	}

	SCREEN_WIDTH = config["screen"]["width"];
	SCREEN_HEIGHT = config["screen"]["height"];

	if (!al_init()) {
		std::cout << "Could not initialize Allegro!" << std::endl;
		exit(-1);
	}

	if (!al_init_image_addon()) {
		std::cout << "Could not initialize Allegro Image Addon!" << std::endl;
		exit(-1);
	}

	if (!al_init_primitives_addon()) {
		std::cout << "Could not initialize Allegro Primitives Addon!" << std::endl;
		exit(-1);
	}

	//Allegro requires installing drivers for all input devices before they can be used.
	al_install_mouse();
	al_install_keyboard();

	//SCREEN_WIDTH += 1300;
	// Create a new display that we can render the image to.
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		std::cout << "Could not initialize Allegro!" << std::endl;
		exit(-1);
	}

	al_set_window_title(display, "Super Mario Bros");
	al_set_window_position(display, 0, 0);

	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());

	viewWin = new Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	gridWin = new Rect(0, 0, 20, 20);
	game = new Game();
}

void Load() {

	tileSet = (Bitmap)al_load_bitmap(TILESET_PATH);

	if (!tileSet) {
		std::cout << "Could not load the TileSet!" << std::endl;
		exit(-1);
	}

	gameMap = new TileLayer(TILEMAP_HEIGHT, TILEMAP_WIDTH, tileSet, Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	if (!gameMap->ReadText(SKY_PATH)) {
		std::cout << "Failed to read Sky Map";
		exit(-1);
	}

	if (!gameMap->ReadText(BACKGROUND_PATH)) {
		std::cout << "Failed to read Background Map";
		exit(-1);
	}

	if (!gameMap->ReadText(FLAG_PATH)) {
		std::cout << "Failed to read Flag Map";
		exit(-1);
	}

	if (!gameMap->ReadText(TERRAIN_PATH)) {
		std::cout << "Failed to read Terrain Map";
		exit(-1);
	}

	//GridUtilities::ComputeTileGridBlocks1(tileLayer->getTileMap(), *grid);
	GridComputation::ComputeTileGridBlocks1(gameMap);
}

void Clear() {
	al_destroy_display(display);
	al_destroy_bitmap((ALLEGRO_BITMAP*)tileSet);
	al_destroy_event_queue(queue);
}

void GridDisplay() {
	//GridUtilities::DisplayGrid(al_get_backbuffer(display), gameMap->GetViewWindow(), *grid, TILEMAP_WIDTH);
	GridComputation::DisplayGrid(al_get_backbuffer(display), gameMap->GetViewWindow(), gameMap->GetGrid()->GetBuffer(), gameMap->GetTotalColumns());
	/*if (TOGGLE_FILLED_RECT) {
		al_draw_filled_rectangle(-viewWin->x + gridWin->x, -viewWin->y + gridWin->y, -viewWin->x + gridWin->x + gridWin->w, -viewWin->y + gridWin->y + gridWin->h, al_map_rgb(255, 0, 0));
	}
	else {
		al_draw_rectangle(-viewWin->x + gridWin->x, -viewWin->y + gridWin->y, -viewWin->x + gridWin->x + gridWin->w, -viewWin->y + gridWin->y + gridWin->h, al_map_rgb(255, 0, 0), 1.0);
	}*/

}

void Render() {
	gameMap->Display(al_get_backbuffer(display));

	if (SHOW_GRID_DEBUG) {
		GridDisplay();
	}

	al_flip_display();
}

void Input() {

	al_get_keyboard_state(&keyboard_state);
	al_get_mouse_state(&mouse_state);

	int keyboard_offset = 4;
	int bef_x = viewWin->x;
	int bef_y = viewWin->y;

	/*GridInput Logic*/
	int basisDx = 4;
	int basisDy = 4;

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_RIGHT)) {

		//ScrollUtilities::ScrollWithBoundsCheck(viewWin, keyboard_offset, 0);
		//tileLayer->SetViewWindow(*viewWin);
		if (gameMap->GetViewWindow().x + gameMap->GetViewWindow().w < SCROLLABLE_TILE_COL * TILE_WIDTH) {

			gameMap->ScrollWithBoundsCheck(keyboard_offset, 0);
		}
		//std::cout << " ------------------------ Pressed Right arrow!" << std::endl;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_LEFT)) {
		//ScrollUtilities::ScrollWithBoundsCheck(viewWin, -keyboard_offset, 0);
		//tileLayer->SetViewWindow(*viewWin);
		gameMap->ScrollWithBoundsCheck(-keyboard_offset, 0);
		std::cout << " ------------------------ Pressed Left arrow!" << std::endl;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_HOME)) {
		//viewWin->x = viewWin->y = 0;
		gameMap->SetViewWindow(Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_END)) {
		/*viewWin->x = MAX_PIXEL_WIDTH - viewWin->w;
		viewWin->y = MAX_PIXEL_HEIGHT - viewWin->h;
		tileLayer->SetViewWindow(*viewWin);*/
		gameMap->SetViewWindow(Rect(MAX_PIXEL_WIDTH - viewWin->w, MAX_PIXEL_HEIGHT - viewWin->h, SCREEN_WIDTH, SCREEN_HEIGHT));
	}

	if (al_mouse_button_down(&mouse_state, 1)) { //1 is left click
		//std::cout << " ------------------------ Pressed Left mouse!" << std::endl;

		int dx = 0, dy = 0;

		//std::cout << "(" << dx << "," << dy << ")" << std::endl;

		/* We did not understand dx,dy meaning in instructions :P */
		if (mouse_state.x > SCREEN_WIDTH / 2) {
			dx = 1;
		}
		else {
			dx = -1;
		}

		if (mouse_state.y > SCREEN_HEIGHT / 2) {
			dy = 1;
		}
		else {
			dy = -1;
		}

		//ScrollUtilities::ScrollWithBoundsCheck(viewWin, dx, dy);
		//tileLayer->SetViewWindow(*viewWin);
		gameMap->ScrollWithBoundsCheck(dx, dy);
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_W)) {
		int dx = 0;
		int dy = -basisDy;

		std::cout << "Pressed W\n";

		GridUtilities::FilterGridMotion(&grid, *gridWin, &dx, &dy);
		gridWin->x += dx;
		gridWin->y += dy;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_S)) {
		int dx = 0;
		int dy = basisDy;

		std::cout << "Pressed S\n";

		GridUtilities::FilterGridMotion(&grid, *gridWin, &dx, &dy);
		gridWin->x += dx;
		gridWin->y += dy;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_D)) {
		int dx = basisDx;
		int dy = 0;

		std::cout << "Pressed D\n";
		//std::cout << "Before: (" << dx << ", " << dy << ")\n";
		GridUtilities::FilterGridMotion(&grid, *gridWin, &dx, &dy);
		//std::cout << "After: (" << dx << ", " << dy << ")\n";
		gridWin->x += dx;
		gridWin->y += dy;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_A)) {
		int dx = -basisDx;
		int dy = 0;

		std::cout << "Pressed A\n";
		GridUtilities::FilterGridMotion(&grid, *gridWin, &dx, &dy);
		gridWin->x += dx;
		gridWin->y += dy;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_1) && al_key_down(&keyboard_state, ALLEGRO_KEY_LCTRL)) {
		SHOW_GRID_DEBUG = 1;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_2) && al_key_down(&keyboard_state, ALLEGRO_KEY_LCTRL)) {
		SHOW_GRID_DEBUG = 0;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_3) && al_key_down(&keyboard_state, ALLEGRO_KEY_LCTRL)) {
		TOGGLE_FILLED_RECT = 0;
	}

	if (al_key_down(&keyboard_state, ALLEGRO_KEY_4) && al_key_down(&keyboard_state, ALLEGRO_KEY_LCTRL)) {
		TOGGLE_FILLED_RECT = 1;
	}

}

void ProgressAnimations() {

}

void AI() {

}

void Physics() {

}

void CollisionChecking() {

}

void UserCode() {
	// hook for custom code at end
}

void CommitDestructions() {

}

bool isFinished() { //h Done? dhladh pote prepei na teleiwsei to paixnidi
	return false;
}

void setGameActions() {
	game->SetRender(Render);
	game->SetInput(Input);
	game->SetProgressAnimations(ProgressAnimations);
	game->SetAI(AI);
	game->SetPhysics(Physics);
	game->SetDestructions(CommitDestructions);
	game->SetCollisionChecking(CollisionChecking);
	game->SetUserCode(UserCode);
	game->SetIsFinished(isFinished);
}

void Run() {
	setGameActions();
	game->MainLoop();

}

void GameMain() {
	Initialise();
	Load();
	Run();
	Clear();
}

/* To remove */
void test_grid() {
	//TileMap *map = tileLayer->getTileMap();
	int total = 0, totalRows = GRID_MAX_HEIGHT, totalColumns = GRID_MAX_WIDTH;
	tmpGrid = new GridIndex[total = totalRows * totalColumns];
	memset(tmpGrid, GRID_EMPTY_TILE, total);
	//GridUtilities::ComputeTileGridBlocks1(tileLayer->getTileMap(), *grid); //a[10][10] -> *a -> a[0][10] || 
	/*for (int i = 0; i < GRID_MAX_HEIGHT; i++) {
		for (int j = 0; j < GRID_MAX_WIDTH; j++) {
			std::cout << (int)*(tmpGrid + i * GRID_MAX_WIDTH + j) << ",";
			/*if (*(tmpGrid + i * GRID_MAX_WIDTH + j) != GRID_EMPTY_TILE) {
				std::cout << "gtxml!\n";
				exit(-1);
			}
		}
		//std::cout << "\n";
	}*/
	//Color testCol = Make32(99, 173, 255, 1);
	//std::cout << "Test Col" << testCol << "\n";
	//GridUtilities::ComputeTileGridBlocks2(tileLayer->getTileMap(), *grid, tileSet, 0, 0); //rgb(99, 173, 255)
}

#endif _GAMEMAIN_H_