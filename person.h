#ifndef PERSON_H
#define PERSON_H

#include "lists.h"

typedef struct {
	int age;
	char* kind;
	List* values;
} Person;

Person* new();
void takeoff(const Person*);

#endif //PERSON_H
