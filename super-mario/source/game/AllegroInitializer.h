#ifndef _ALLEGROINITIALIZER_H_
#define _ALLEGROINITIALIZER_H_

#include "./GameVars.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"

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

		if (!al_install_audio()) { //the order of these three is important
			std::cout << "Could not install Allegro Audio!" << std::endl;
			exit(-1);
		}

		if(!al_init_acodec_addon()) {
			std::cout << "Could not initialize Allegro Audio Codec Addon!" << std::endl;
			exit(-1);
		}

		al_reserve_samples(2); //can play 2 sounds at the same time

		//Allegro requires installing drivers for all input devices before they can be used.
		if (!al_install_mouse()) {
			std::cout << "Could not install Allegro Mouse!" << std::endl;
			exit(-1);
		}

		if (!al_install_keyboard()) {
			std::cout << "Could not install Allegro Keyboard!" << std::endl;
			exit(-1);
		}

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
