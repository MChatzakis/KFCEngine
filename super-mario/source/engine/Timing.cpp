#include "Timing.h"

SystemClock SystemClock::singleton;

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

auto SystemClock::Get(void) -> SystemClock&
{
	return singleton;
}
