#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "timeops.h"

void randomize() {
	srand(ntime() * getpid() % time(NULL));
}

int rnd(int const min, int const max) {
	return min + rand() % (max + 1 - min);
}
