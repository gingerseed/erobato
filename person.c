#include <stdio.h>
#include <stdlib.h>
#include "strops.h"
#include "person.h"
#include "data.h"
#include "rnd.h"
#include "arrops.h"

#define WARDROBE_SIZE 6

Person* new() {
	Person* person = malloc(sizeof(Person));
	if (!person) {
		goto error;
	}

	person->age = rnd(MIN_AGE, MAX_AGE);
	person->kind = person->age > 26 ? "woman" : person->age >= 18 ? "girl" : "teenage girl";
	person->count = 0;

	person->clothing = malloc(0);
	if (person->clothing == NULL) {
		goto error;
	}

	append(&person->clothing, person->count++,combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier1[rnd(0, TIER1_SIZE - 1)]));
	append(&person->clothing, person->count++,combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier2[rnd(0, TIER2_SIZE - 1)]));

	if (rnd(0, 99) % 2 > 0) {
		append(&person->clothing, person->count++,combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier3[rnd(0, TIER3_SIZE - 1)]));
	}else {
		append(&person->clothing, person->count++,combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier7[rnd(0, TIER7_SIZE - 1)]));
	}

	append(&person->clothing, person->count++,combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier5[rnd(0, TIER5_SIZE - 1)]));

	if (rnd(0, 99) % 3 < 1) {
		append(&person->clothing, person->count++,combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier4[rnd(0, TIER4_SIZE - 1)]));
	}

	if (rnd(0, 99) % 3 > 1) {
		append(&person->clothing, person->count++,combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier8[rnd(0, TIER8_SIZE - 1)]));
	}

	append(&person->clothing, person->count++,combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier6[rnd(0, TIER6_SIZE - 1)]));

	return person;

	error:
	free(person);
	return NULL;
}

void takeoff(Person* person) {
	if (person->count < 1) {
		return;
	}

	free(person->clothing[person->count - 1]);
	person->count--;
}
