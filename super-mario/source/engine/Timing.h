#ifndef _TIMING_H_
#define _TIMING_H_

#define CurrTime() SystemClock::Get().milli_secs() //returns the current time in milliseconds

#include <chrono>
class SystemClock final {
private:
	std::chrono::high_resolution_clock clock;
	static SystemClock singleton;
public:
	static auto Get(void)->SystemClock&;
	uint64_t milli_secs(void) const;
	uint64_t micro_secs(void) const;
	uint64_t nano_secs(void) const;
};

uint64_t GetSystemTime(void);

#endif _TIMING_H_