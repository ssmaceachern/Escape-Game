#include <time.h>
#include "Clock.h"



inline long tsToUsec(struct timespec& ts) {
	return (ts.tv_sec * 1000) + (ts.tv_nsec / 1000000);
}


Clock::Clock() {
	clock_gettime(CLOCK_REALTIME, &prev_ts);
}

long Clock::delta() {
	long result = tsToUsec(prev_ts);
	return result;
}

long Clock::split() {
	long result = delta();
	Clock();
	long time_now = tsToUsec(prev_ts);
	return time_now - result;
}

