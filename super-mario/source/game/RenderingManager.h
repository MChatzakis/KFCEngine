#ifndef _RENDERINGMANAGER_H_
#define _RENDERINGMANAGER_H_

#include "./GameVars.h"
#include "./Mario.h"
#include "./engine/Sprite.h"

#include "./TopTexts.h"

void GridDisplay() {
	GridComputation::DisplayGrid(al_get_backbuffer(display), gameMap->GetViewWindow(), gameMap->GetGrid()->GetBuffer(), gameMap->GetTotalColumns());
}

void Render() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	gameMap->Display(al_get_backbuffer(display));
	
	TopTexts::GetSingleton().DrawText(Mario::GetSingleton().getScore(), Mario::GetSingleton().getTotalLifes(), Mario::GetSingleton().getCoins());

	Rect screen = Rect(0, 0, gameMap->GetViewWindow().w, gameMap->GetViewWindow().h);
	for (auto c : SpriteManager::GetSingleton().GetDisplayList()) {
		c->Display(al_get_backbuffer(display), screen, clipper);
	}

	if (SHOW_GRID_DEBUG) {
		GridDisplay();
	}

	al_flip_display();
}


#endif _RENDERINGMANAGER_H_