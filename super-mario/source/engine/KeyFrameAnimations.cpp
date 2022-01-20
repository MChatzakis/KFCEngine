#include "./KeyFrameAnimations.h"

void Animate(void) {
	uint64_t t = 0;
	for (auto i = 0; i < TOTAL_KEY_FRAMES; )
		if (CurrTime() >= t) {
			t = CurrTime() + FRAME_DELAY;
			auto b = keyFrames[i];
			Vsync();
			BitmapClear(BitmapGetScreen(), BLACK_COLOR); //!
			MaskedBlit(b, { 0, 0, BitmapGetWidth(b), BitmapGetHeight(b) }, BitmapGetScreen(), framePositions[i++]);
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