#ifndef _TOPTEXTS_H_
#define _TOPTEXTS_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <string>

class TopTexts {
private:
	static TopTexts texts;
	ALLEGRO_FONT* font;

	int offset = 5;
	
public:

	static auto GetSingleton(void)->TopTexts&;
	static auto GetSingletonConst(void) -> const TopTexts&;

	void Initialize(const char* fontPath, int size);

	void setFont(ALLEGRO_FONT* _font);

	ALLEGRO_FONT* getFont();

	void DrawText(int score, int lifes, int coins, int centerAroundX, int centerAroundY);

};


#endif _TOPTEXTS_H_
