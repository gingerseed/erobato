#ifndef PERSON_H
#define PERSON_H

#include "lists.h"

typedef struct {
	int age;
	char* kind;
	List* values;
} Person;

Person* new();
#endif //PERSON_H
