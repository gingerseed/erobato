#ifndef LISTS_H
#define LISTS_H

typedef struct {
	unsigned int length;
	char** data;
} List;

List* make() ;
int append(List*, char*);
int erase(List*);

#endif //LISTS_H
