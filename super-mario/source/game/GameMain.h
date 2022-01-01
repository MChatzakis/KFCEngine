#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "../utils/Utils.h"

#include "../engine/General.h"
#include "../engine/Game.h"
#include "../engine/TileLayer.h"

/* Global Stuff */
int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

/*ALLEGRO related*/
ALLEGRO_BITMAP* tileSet;
ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* queue;

#define TILESET_PATH "resources/bitmaps/tileset.png"
#define SKY_PATH "resources/csv/level1-1_Sky.csv"
#define BACKGROUND_PATH "resources/csv/level1-1_background.csv"
#define TERRAIN_PATH "resources/csv/level1-1_terain.csv"

Rect* viewWin;
Game* game;
TileLayer* tileLayer;

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

	viewWin = new Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	game = new Game();
	//tileLayer = new TileLayer();
	
}

void Load() {

	tileSet = al_load_bitmap(TILESET_PATH);
	if (!tileSet) {
		std::cout << "Could not load the TileSet!" << std::endl;
		exit(-1);
	}

	tileLayer = new TileLayer(tileSet);

	if (!tileLayer->ReadText(SKY_PATH)) {
		std::cout << "Failed to read Sky Map";
		exit(-1);
	}
	
	if (!tileLayer->ReadText(BACKGROUND_PATH)) {
		std::cout << "Failed to read Background Map";
		exit(-1);
	}

	if (!tileLayer->ReadText(TERRAIN_PATH)) {
		std::cout << "Failed to read Terrain Map";
		exit(-1);
	}

	//TileUtilities::printTileMap_DEBUG((TileMap *)tileLayer->getTileMap());

	//TileUtilities::ReadTextMap(&map, SKY_PATH);
	//TileUtilities::ReadTextMap(&map, BACKGROUND_PATH);
	//TileUtilities::ReadTextMap(&map, TERRAIN_PATH);

}

void Clear() {
	al_destroy_display(display);
	al_destroy_bitmap(tileSet);
	al_destroy_event_queue(queue);
}

void Render() {
	//ScrollUtilities::TileTerrainDisplay((TileMap*)tileLayer->getTileMap(), NULL, *viewWin, (Bitmap*)tileSet);
	tileLayer->Display(al_get_backbuffer(display), Rect());
	al_flip_display();
}

void Input() {
	ALLEGRO_EVENT event;

	al_wait_for_event(queue, &event);
	
	switch (event.type) {
	case ALLEGRO_EVENT_KEY_DOWN:
		switch (event.keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:
			std::cout << " ------------------------ Pressed Escape!" << std::endl;
			break;
		case ALLEGRO_KEY_RIGHT:
			std::cout << "Before " << viewWin->x << std::endl;
			ScrollUtilities::ScrollWithBoundsCheck(viewWin, 16, 0);
			tileLayer->SetViewWindow(*viewWin);
			std::cout << "After " << viewWin->x << std::endl;
			std::cout << " ------------------------ Pressed Right arrow!" << std::endl;
			break;
		case ALLEGRO_KEY_LEFT:
			ScrollUtilities::ScrollWithBoundsCheck(viewWin, -16, 0);
			tileLayer->SetViewWindow(*viewWin);
			std::cout << " ------------------------ Pressed Left Arrow!" << std::endl;
			break;
		case ALLEGRO_KEY_SPACE:
			std::cout << " ------------------------ Pressed Space!" << std::endl;
			break;
		}
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		std::cout << " ------------------------ Pressed a mouse button!" << std::endl;
		break;
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