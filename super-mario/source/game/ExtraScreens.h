#ifndef _EXTRASCREENS_H_
#define _EXTRASCREENS_H_

#include "./GameVars.h"

class ExtraScreens {
private:
	static ExtraScreens screens;
public:
	static auto GetSingleton(void) -> ExtraScreens& { return screens; }
	static auto GetSingletonConst(void) -> const ExtraScreens& { return screens; }

	void DispScreen(std::string imagePath) {
		ALLEGRO_BITMAP* bitmap = al_load_bitmap(imagePath.c_str());
		
		al_draw_bitmap(bitmap, 0, 0, 0);
		al_flip_display();

		ALLEGRO_KEYBOARD_STATE keyboard_state;
		ALLEGRO_MOUSE_STATE mouse_state;

		al_get_keyboard_state(&keyboard_state);
		al_get_mouse_state(&mouse_state);

		while (!al_key_down(&keyboard_state, ALLEGRO_KEY_SPACE)) {
			al_get_keyboard_state(&keyboard_state);
			al_get_mouse_state(&mouse_state);
		}
	}
};

ExtraScreens ExtraScreens::screens;

#endif _EXTRASCREENS_H_