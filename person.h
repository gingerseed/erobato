#ifndef PERSON_H
#define PERSON_H

typedef struct {
	int age;
	char* kind;
	int count;
	char** clothing;
} Person;

Person* new();
void takeoff(Person*);

#endif //PERSON_H
