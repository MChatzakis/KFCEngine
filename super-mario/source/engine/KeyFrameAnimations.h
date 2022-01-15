#ifndef _KEYFRAMEANIMATIONS_H
#define _KEYFRAMEANIMATIONS_H

#include "./General.h"
#include "./Timing.h"
#include "./AnimationFilm.h"


#define TOTAL_KEY_FRAMES 10 //total bitmaps of main character
#define FRAME_DELAY 50 //fps?
#define BLACK_COLOR 0

//CLASS WITH FIELDS: frame_delay, keyFrames, framePositions and function void Animate(void) ?
Bitmap keyFrames[TOTAL_KEY_FRAMES];
Point framePositions[TOTAL_KEY_FRAMES];
void Animate(void) {
	uint64_t t = 0;
	for (auto i = 0; i < TOTAL_KEY_FRAMES; )
		if (CurrTime() >= t) {
			t = CurrTime() + FRAME_DELAY;
			auto b = keyFrames[i];
			Vsync();
			BitmapClear(BitmapGetScreen(), BLACK_COLOR);
			MaskedBlit(
				b,
				{ 0, 0, BitmapGetWidth(b), BitmapGetHeight(b) },
				BitmapGetScreen(),
				framePositions[i++]
			);
		}
}

void Animate(const AnimationFilm& film, const Point& at) {
	uint64_t t = 0;
	for (byte i = 0; i < film.GetTotalFrames(); )
		if (CurrTime() >= t) {
			t = CurrTime() + FRAME_DELAY;
			Vsync();
			BitmapClear(BitmapGetScreen(), BLACK_COLOR);
			film.DisplayFrame(BitmapGetScreen(), at, i++);
		}
}

#endif _KEYFRAMEANIMATIONS_H