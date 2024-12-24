#include <stdio.h>
#include <stdlib.h>
#include "strops.h"
#include "person.h"
#include "data.h"
#include "rnd.h"
#include "colors.h"

#define WARDROBE_SIZE 6

Person* new() {
	Person* person = malloc(sizeof(Person));
	if (!person) {
		goto error;
	}

	person->age = rnd(MIN_AGE, MAX_AGE);
	person->kind = person->age > 42 ? "milf" : person->age > 26 ? "woman" : person->age >= 18 ? "girl" : "teenage girl";
	person->values = make();

	append(person->values, combine(2, " ", pick_color(), tier1[rnd(0, TIER1_SIZE - 1)]));

	append(person->values, combine(2, " ", pick_color(), tier2[rnd(0, TIER2_SIZE - 1)]));

	if (rnd(0, 99) % 2 > 0) {
		append(person->values, combine(2, " ", pick_color(), tier3[rnd(0, TIER3_SIZE - 1)]));
	} else {
		append(person->values, combine(2, " ", pick_color(), tier7[rnd(0, TIER7_SIZE - 1)]));
	}

	append(person->values, combine(2, " ", pick_color(), tier5[rnd(0, TIER5_SIZE - 1)]));

	if (rnd(0, 99) % 3 < 1) {
		append(person->values, combine(2, " ", pick_color(), tier4[rnd(0, TIER4_SIZE - 1)]));
	}

	if (rnd(0, 99) % 3 > 1) {
		append(person->values, combine(2, " ", pick_color(), tier8[rnd(0, TIER8_SIZE - 1)]));
	}

	append(person->values, combine(2, " ", pick_color(), tier6[rnd(0, TIER6_SIZE - 1)]));
	return person;

	error:
	free(person);
	return NULL;
}

void takeoff(const Person* person) {
	if (person->values->length < 1) {
		return;
	}

	free(person->values->data[person->values->length - 1]);
	person->values->length--;
}
