#ifndef _FPSCalculator_H_
#define _FPSCalculator_H_

#include <chrono>

class FPSCalculator {
private:
	int fps;
	int newFps;
	uint64_t timeStamp;
	
	static FPSCalculator calculator;


public:

	static auto Get(void)->FPSCalculator&;

	FPSCalculator();

	int GetFPS();
	void CalculateFPS();

};

#endif _FPSCalculator_H_