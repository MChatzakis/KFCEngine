#include <iostream>
#include <string>

#include <allegro5/allegro.h>
#include <nlohmann/json.hpp>

int main() {
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	al_set_window_position(display, 0, 0);


}