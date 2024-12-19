#include <stdlib.h>

int rnd(int const min, int const max) {
	return min + rand() % (max + 1 - min);
}
