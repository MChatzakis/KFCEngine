#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include "./GameVars.h"

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
		SoundsManager::GetSingleton().PlaySound("small_mario_jump");

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


#endif _INPUTMANAGER_H_