#ifndef _ALLEGROINITIALIZER_H_
#define _ALLEGROINITIALIZER_H_

#include "./GameVars.h"

class AllegroInitializer {
public:
	static void initializeAllegro() {
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
	}
};
#endif _ALLEGROINITIALIZER_H_
