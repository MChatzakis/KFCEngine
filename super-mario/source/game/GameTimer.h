#ifndef _GAMETIMER_H_
#define _GAMETIMER_H_

#include "../engine/Timing.h"

class GameTimer {
private:
	static GameTimer timer;
	uint64_t time;

public:
	static auto GetSingleton(void)->GameTimer&;
	static auto GetSingletonConst(void) -> const GameTimer&;

	void init();

	uint64_t GetTimeInSeconds();

};

#endif _GAMETIMER_H_