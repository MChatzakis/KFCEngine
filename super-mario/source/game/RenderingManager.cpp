#include "./RenderingManager.h"
#include "./GameTimer.h"
#include "../engine/FPSCalculator.h"

void GridDisplay() {
	GridComputation::DisplayGrid(al_get_backbuffer(display), gameMap->GetViewWindow(), gameMap->GetGrid()->GetBuffer(), gameMap->GetTotalColumns());
}

void Render() {
	al_clear_to_color(al_map_rgb(0, 0, 0));

	//gameMap->Display(al_get_backbuffer(display));
	gameMap->ConstantDisplay(al_get_backbuffer(display));

	TopTexts::GetSingleton().DrawText(Mario::GetSingleton().getScore(), Mario::GetSingleton().getTotalLifes(), Mario::GetSingleton().getCoins(), GameTimer::GetSingleton().GetTimeInSeconds(), FPSCalculator::Get().GetFPS(), SCREEN_WIDTH / 2, 2);
	
	Rect screen = Rect(0, 0, gameMap->GetViewWindow().w, gameMap->GetViewWindow().h);
	for (auto c : SpriteManager::GetSingleton().GetDisplayList()) {
		c->Display(al_get_backbuffer(display), screen, clipper);
	}

	if (SHOW_GRID_DEBUG) {
		GridDisplay();
	}

	if (game->IsPaused()) {
		TopTexts::GetSingleton().DrawPauseText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}

	al_flip_display();

	FPSCalculator::Get().CalculateFPS();
}