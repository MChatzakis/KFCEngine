#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "utils/Utils.h"

#include "engine/Tilemap.h"
#include "engine/ViewWindow.h"

#include "./TypeDefinitions.h"
/*
1) Finalize the Map (+ Game over, Start, Round complete screens) => KONTO
2) Make some function for JSON read => (FANOU, MANOS)
3) Go through lectures 6,7,8,9 for display function and view window => OLOI
4) Try to display tiles => FANOU
5) Input logic for view window => MANOS
6) Find out what is going on with back buffer etc. => MANOS
*/

void loadMap();

int main() {
	int SCREEN_WIDTH = 0;
	int SCREEN_HEIGHT = 0;

	nlohmann::json config = readJSON("resources/config/config.json");
	if (config != NULL) {
		SCREEN_WIDTH = config["screen"]["width"];
		SCREEN_HEIGHT = config["screen"]["height"];

		std::cout << "Screen width = " << config["screen"]["width"] << ", height = " << config["screen"]["height"] << std::endl;
		//config["screen"]["height"] = 480;
		//writeJSON(config, "resources/config/config.json", 2); //indent -> spaces
	}

	if (!al_init()) {
		std::cout << "Could not initialize Allegro!" << std::endl;
		exit(-1);
	}

	if (!al_init_image_addon()) {
		std::cout << "Could not initialize Allegro Image Addon!" << std::endl;
		exit(-1);
	}

	//Allegro requires installing drivers for all input devices before they can be used.
	al_install_mouse();
	al_install_keyboard();

	// Create a new display that we can render the image to.
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!display) {
		std::cout << "Could not initialize Allegro!" << std::endl;
		exit(-1);
	}

	al_set_window_title(display, "Window");
	al_set_window_position(display, 0, 0);

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_mouse_event_source());

	ALLEGRO_BITMAP* tileSet = al_load_bitmap("resources/bitmaps/tileset.png");
	if (!tileSet) {
		std::cout << "Could not load the TileSet!" << std::endl;
		exit(-1);
	}

	Rect* viewWin = new Rect();
	viewWin->x = 0;
	viewWin->y = 0;
	viewWin->h = SCREEN_HEIGHT;
	viewWin->w = SCREEN_WIDTH;

	loadMap();

	ALLEGRO_EVENT event;
	int onGoingGameLoop = 1;
	while (onGoingGameLoop) {

		al_wait_for_event(queue, &event);
		TileTerrainDisplay(&map, NULL, *viewWin, Rect(), (Bitmap *)tileSet);

		switch (event.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
			onGoingGameLoop = 0;
			std::cout << " ------------------------ Pressed a keyboard button!" << std::endl;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			onGoingGameLoop = 0;
			std::cout << " ------------------------ Pressed a mouse button!" << std::endl;
			break;
		}

		//Copies or updates the front and back buffers so that what has been drawn previously on the currently selected display becomes visible on screen. Pointers to the special back and front buffer bitmaps remain valid and retain their semantics as back and front buffers respectively, although their contents may have changed.
		al_flip_display();
	}
	
	
	return 0;
}

void loadMap() {
	//Instead of .. put your path
	if (!ReadTextMap(&map, "resources/csv/level1-1_Sky.csv")) {
		std::cout << "Failed to read map";
		exit(-1);
	}
	if (!ReadTextMap(&map, "resources/csv/level1-1_background.csv")) {
		std::cout << "Failed to read map";
		exit(-1);
	}

	if (!ReadTextMap(&map, "resources/csv/level1-1_flag.csv")) {
		std::cout << "Failed to read map";
		exit(-1);
	}

	if (!ReadTextMap(&map, "resources/csv/level1-1_terain.csv")) {
		std::cout << "Failed to read map";
		exit(-1);
	}

	//WriteTextMap(&map, "resources/csv/full-map.csv");
	//printTileMap_DEBUG(&map);


}