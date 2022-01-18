#ifndef _KEYFRAMEANIMATIONS_H
#define _KEYFRAMEANIMATIONS_H

#include "./General.h"
#include "./Timing.h"
#include "./AnimationFilm.h"

#define TOTAL_KEY_FRAMES 10 //total bitmaps of main character
#define FRAME_DELAY 50 //fps?
#define BLACK_COLOR 0

Bitmap keyFrames[TOTAL_KEY_FRAMES];
Point framePositions[TOTAL_KEY_FRAMES];

void Animate(void);

void Animate(const AnimationFilm& film, const Point& at);

#endif _KEYFRAMEANIMATIONS_H