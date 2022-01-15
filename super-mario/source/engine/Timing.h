#ifndef _TIMING_H_
#define _TIMING_H_

#define CurrTime() SystemClock::Get().milli_secs() //returns the current time in milliseconds

#include <chrono>
class SystemClock final {
private:
	std::chrono::high_resolution_clock clock;
	static SystemClock singleton;
public:
	static auto Get(void) -> SystemClock&
	{
		return singleton;
	}
	uint64_t milli_secs(void) const;
	uint64_t micro_secs(void) const;
	uint64_t nano_secs(void) const;
};

uint64_t SystemClock::milli_secs(void) const {
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(clock.now().time_since_epoch()).count();
}

uint64_t SystemClock::micro_secs(void) const {
	return std::chrono::duration_cast<std::chrono::microseconds>
		(clock.now().time_since_epoch()).count();
}

uint64_t SystemClock::nano_secs(void) const {
	return std::chrono::duration_cast<std::chrono::nanoseconds>
		(clock.now().time_since_epoch()).count();
}

uint64_t GetSystemTime(void) {
	return SystemClock::Get().milli_secs();
}

#endif _TIMING_H_