#include "TopTexts.h"

TopTexts TopTexts::texts;

auto TopTexts::GetSingleton(void) -> TopTexts& { return texts; }
auto TopTexts::GetSingletonConst(void) -> const TopTexts& { return texts; }

void TopTexts::Initialize(const char* fontPath, int size) {
	font = al_load_ttf_font(fontPath, size, 0);
}

void TopTexts::setFont(ALLEGRO_FONT* _font) {
	font = _font;
}

ALLEGRO_FONT* TopTexts::getFont() {
	return font;
}

void TopTexts::DrawText(int score, int lifes, int coins, int timePassed,int centerAroundX, int centerAroundY) {
	std::string text = "SCORE:" + std::to_string(score) + " LIFES:" + std::to_string(lifes) + " LEVEL:1-1 COINS:" + std::to_string(coins) + " TIME: " + std::to_string(timePassed);
	al_draw_text(font, al_map_rgb(255, 255, 255), centerAroundX, centerAroundY, ALLEGRO_ALIGN_CENTER, text.c_str());
}