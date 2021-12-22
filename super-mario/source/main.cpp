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
2) Make some function for JSON read => (FANOU, MANOS) DONE
3) Go through lectures 6,7,8,9 for display function and view window => OLOI
4) Try to display tiles => FANOU DONE
5) Input logic for view window => MANOS
6) Find out what is going on with back buffer etc. => MANOS
*/

void loadMap();

/* Global Stuff */
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

/*ALLEGRO related*/
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_BITMAP* tileSet;


int main() {
	
	nlohmann::json config = readJSON("resources/config/config.json");
	if (config == NULL) {
		std::cout << "Cannot open configuration file!" << std::endl;
		exit(-1);
	}
	SCREEN_WIDTH = config["screen"]["width"];
	SCREEN_HEIGHT = config["screen"]["height"];

	//std::cout << "Screen width = " << config["screen"]["width"] << ", height = " << config["screen"]["height"] << std::endl;

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

	tileSet = al_load_bitmap("resources/bitmaps/tileset.png");
	if (!tileSet) {
		std::cout << "Could not load the TileSet!" << std::endl;
		exit(-1);
	}

	Rect* viewWin = new Rect(200, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	loadMap();

	ALLEGRO_EVENT event;
	int onGoingGameLoop = 1;
	while (onGoingGameLoop) {

		al_wait_for_event(queue, &event);
		//clean display/backbuffer i dont know
		dpyBuffer = (ALLEGRO_BITMAP*)al_get_backbuffer(display);

		ALLEGRO_BITMAP* sky = al_create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
		ALLEGRO_BITMAP* terrain = al_create_sub_bitmap(sky, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		al_set_target_bitmap(terrain);
		TileTerrainDisplay(&map, NULL, *viewWin, Rect(), (Bitmap*)tileSet);
		al_set_target_bitmap(sky);
		TileTerrainDisplay(&map_sky, NULL, *viewWin, Rect(), (Bitmap*)tileSet);
		al_set_target_bitmap((ALLEGRO_BITMAP*)dpyBuffer);
		
		al_draw_bitmap(sky, 0, 0, 0);
		al_flip_display();

		switch (event.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				onGoingGameLoop = 0;
				std::cout << " ------------------------ Pressed Escape!" << std::endl;
				break;
			case ALLEGRO_KEY_RIGHT:
				std::cout << "Before " << viewWin->x << std::endl;
				ScrollWithBoundsCheck(viewWin, 1, 0);
				std::cout << "After " << viewWin->x << std::endl;

				std::cout << " ------------------------ Pressed Right arrow!" << std::endl;
				break;
			case ALLEGRO_KEY_LEFT:
				ScrollWithBoundsCheck(viewWin, -1, 0);
				std::cout << " ------------------------ Pressed Left Arrow!" << std::endl;
				break;
			case ALLEGRO_KEY_SPACE:
				std::cout << " ------------------------ Pressed Space!" << std::endl;
				break;
			}

			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			onGoingGameLoop = 0;
			std::cout << " ------------------------ Pressed a mouse button!" << std::endl;
			break;
		}

		//Copies or updates the front and back buffers so that what has been drawn previously on the currently selected display becomes visible on screen. Pointers to the special back and front buffer bitmaps remain valid and retain their semantics as back and front buffers respectively, although their contents may have changed.
		al_flip_display();
		al_destroy_bitmap(terrain);
		al_destroy_bitmap(sky);
	}

	al_destroy_display(display);
	al_destroy_bitmap(tileSet);
	al_destroy_event_queue(queue);

	return 0;
}

void loadMap() {
	//Instead of .. put your path
	if (!ReadTextMap(&map_sky, "resources/csv/level1-1_Sky.csv")) {
		std::cout << "Failed to read map";
		exit(-1);
	}
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