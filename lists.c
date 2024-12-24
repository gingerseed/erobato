#include "lists.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* make() {
	List* list = malloc(sizeof(List));
	if (list == NULL) {
		goto error;
	}

	list->length = 0;
	list->data = malloc(0);
	return list;

	error:
	free(list);
	return NULL;
}

int append(List* list, char* value) {
	char** tmp = realloc(list->data, sizeof(char*) * (list->length + 1));
	if (tmp == NULL) {
		return -1;
	}

	list->data = tmp;
	list->data[list->length] = value;

	return ++list->length;
}

int erase(List* list) {
	if (list->length < 1) {
		return -1;
	}

	free(list->data[--list->length]);
	return list->length;
}
