#include "arrops.h"

#include <stdio.h>
#include <stdlib.h>

int append(char*** arr, int length, char* value) {
	char** tmp = realloc(*arr, sizeof(char*) * ++length);
	if (tmp == NULL) {
		return -1;
	}

	*arr = tmp;
	(*arr)[length - 1] = value;

	return length;
}
