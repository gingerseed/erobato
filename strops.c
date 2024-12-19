#include <stdlib.h>
#include <stdarg.h>
#include <strings.h>

char* combine(int const count, char const* sp, ...) {
	long unsigned size = 1;

	char* result = malloc(size * sizeof(char*));
	if (result == NULL) {
		goto error;
	}

	va_list p;
	va_start(p, sp);

	for (int i = 0; i < count; i++) {
		char const* frn = va_arg(p, char*);
		size += strlen(frn);

		if (i > 0) {
			size += strlen(sp);
		}

		char* n = realloc(result, size * sizeof(char));
		if (!n) {
			goto error;
		}

		result = n;
		if (i > 0) {
			strcat(result, sp);
		}

		strcat(result, frn);
	}

	va_end(p);
	return result;

	error:
	free(result);
	return NULL;
}

void swap(char** a, char** b) {
	if (a == b) {
		return;
	}

	char* t = *a;
	*a = *b;
	*b = t;
}
