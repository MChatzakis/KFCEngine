#include <iostream>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <nlohmann/json.hpp>

int main() {
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

	//ALLEGRO_BITMAP* bitmap;
	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* queue;

	if (!al_init()) {
		std::cout << "Could not initialize Allegro!" << std::endl;
		exit(-1);
	}

	/* Allegro requires installing drivers for all input devices before
	 * they can be used.
	 */
	al_install_mouse();
	al_install_keyboard();

	/* Initialize the image addon. Requires the allegro_image addon
	 * library.
	 */
	al_init_image_addon();
	// Create a new display that we can render the image to.
	ALLEGRO_DISPLAY* display = al_create_display(640, 480);
	if (!display) {
		std::cout << "Could not initialize Allegro!" << std::endl;
		exit(-1);
	}

	al_set_window_title(display, "Window");

	 //= al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);

	al_set_window_position(display, 0, 0);


}