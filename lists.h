#ifndef LISTS_H
#define LISTS_H

typedef struct {
	unsigned int length;
	char** data;
} List;

List* make() ;
int append2(List*, char*);

#endif //LISTS_H
