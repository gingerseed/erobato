#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "data.h"
#include "person.h"
#include "rnd.h"
#include "strops.h"

#define TURNS_COUNT 6

int main(void) {
	randomize();

	Person* person = new();
	if (person == NULL) {
		return 1;
	}

	int money = 1000;
	printf("You are playing with a %s %d years old %s %s.\n",
		adjective[rnd(0, ADJECTIVES_SIZE - 1)], person->age, races[rnd(1, RACES_NUM - 1)], person->kind);

	int turns = 0;

	int p_move, o_move;
	while (person->values->length > 0 && money > 0) {
		printf("\n");
		printf("She is wearing: \n");

		for (int i = 0; i < person->values->length; i++) {
			if (strlen(person->values->data[i]) > 0) {
				printf("* %s\n", person->values->data[i]);
			}
		}

		o_move = rnd(0, GESTURES_SIZE - 1);
		printf("\n");

		printf("You have $%d.\n", money);
		if (turns > 0) {
			printf("Are you ready for the next round?\n");
		} else {
			printf("Please make your move!\n");
		}

		for (int i = 0; i < GESTURES_SIZE; i++) {
			printf("[%d] -> %s\n", i + 1, gestures[i]);
		}

		printf("Your choose:");
		while (scanf("%d", &p_move) != 1 || p_move < 1 || p_move > GESTURES_SIZE) {
			scanf("%*[^\n]");
			printf("Your choose:");
		}

		p_move--;
		printf("\n");

		printf("You chose: %s\n", gestures[p_move]);
		printf("You opponent chose: %s\n", gestures[o_move]);
		printf("\n");

		if (o_move == p_move) {
			printf("It's a draw! You are loosing $50.\n");
			money -= 50;
			continue;
		}

		if (p_move == 0 && o_move == 1) {
			goto lose;
		}

		if (p_move == 1 && o_move == 2) {
			goto lose;
		}

		if (p_move == 2 && o_move == 0) {
			goto lose;
		}

		printf("You won!\n");
		if (person->values->length > 1 && rnd(0, 99) % 3 == 0) {
			swap(&person->values->data[person->values->length - 1], &person->values->data[person->values->length - 2]);
		}

		printf("She is slowly taking off her %s.\n", person->values->data[person->values->length - 1]);
		takeoff(person);

		turns++;
		continue;

		lose:
		printf("You lost! I will cost you $100.\n");
		money -= 100;
	}

	if (money > 0) {
		printf("\"Oh, you nailed it!\" - said the %s sitting totally naked in the %s pose.\n",
			person->kind, adjective[rnd(0, ADJECTIVES_SIZE - 1)]);
	} else {
		printf("\"Such a loser\" - the %s is laughing at you!\n", person->kind);
	}

	while (person->values->length > 0) {
		takeoff(person);
	}

	free(person);
	return 0;
}
