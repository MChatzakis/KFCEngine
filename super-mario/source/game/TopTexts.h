#ifndef _TOPTEXTS_H_
#define _TOPTEXTS_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>

class TopTexts {
private:
	static TopTexts texts;
	ALLEGRO_FONT* font;

	int offset = 5;
	
public:

	static auto GetSingleton(void) -> TopTexts& { return texts; }
	static auto GetSingletonConst(void) -> const TopTexts& { return texts; }

	void Initialize(const char* fontPath, int size) {
		font = al_load_ttf_font(fontPath, size, 0);
	}

	void setFont(ALLEGRO_FONT* _font) {
		font = _font;
	}

	ALLEGRO_FONT* getFont() {
		return font;
	}

	void DrawText(int score, int lifes, int coins) {
		std::string text = "SCORE:" + std::to_string(score) + " LIFES:" + std::to_string(lifes) + " LEVEL:1-1 COINS:" + std::to_string(coins);
		al_draw_text(font, al_map_rgb(255, 255, 255), 0, 2, 0, text.c_str());
	}

};

TopTexts TopTexts::texts;

#endif _TOPTEXTS_H_
