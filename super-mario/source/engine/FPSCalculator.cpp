#include "./FPSCalculator.h"

#include "./Timing.h"

#define SEC 1000

FPSCalculator FPSCalculator::calculator;

FPSCalculator::FPSCalculator() {
	fps = 0;
	newFps = 0;
	timeStamp = 0;
}

int FPSCalculator::GetFPS() {
	return fps;
}

void FPSCalculator::CalculateFPS() {
	uint64_t ct = CurrTime();

	if (ct - timeStamp >= SEC) {
		fps = newFps;
		newFps = 0;
		timeStamp = ct;
	}
	else {
		newFps++;
	}
}

auto FPSCalculator::Get(void) -> FPSCalculator&
{
	return calculator;
}