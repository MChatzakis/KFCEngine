#include "ExtraScreens.h"

ExtraScreens ExtraScreens::screens;

auto ExtraScreens::GetSingleton(void) -> ExtraScreens& { return screens; }
auto ExtraScreens::GetSingletonConst(void) -> const ExtraScreens& { return screens; }

void ExtraScreens::DispScreen(std::string imagePath) {
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