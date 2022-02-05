#include "./GameTimer.h"
#include <math.h> 

GameTimer GameTimer::timer;

auto GameTimer::GetSingleton(void) -> GameTimer& { return timer; }
auto GameTimer::GetSingletonConst(void) -> const GameTimer& { return timer; }

void GameTimer::init() {
	time = CurrTime();
}

uint64_t GameTimer::GetTimeInSeconds() {
	uint64_t timePassed = 0;

	timePassed = round((CurrTime() - time)/1000);

	return timePassed;
	
}

