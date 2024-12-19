#include <stdio.h>
#include <stdint.h>
#include <time.h>

long ntime() {
	struct timespec ts;

	if (timespec_get(&ts, TIME_UTC) == 0) {
		return UINT64_MAX;
	}

	return ts.tv_nsec;
}
