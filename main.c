#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#define MIN_AGE 12
#define MAX_AGE 46

#define ADJECTIVES_SIZE 9
static char* adjective[ADJECTIVES_SIZE] = {
	"shy",
	"bashful",
	"timorous",
	"confident",
	"brash",
	"coy",
	"shameless",
	"audacious",
	"wanton",
};

#define RACES_NUM 12
static char* races[RACES_NUM] = {
	"American",
	"Asian",
	"Filipino",
	"Slovenian",
	"German",
	"French",
	"Spanish",
	"Brazilian",
	"Ukrainian",
	"African",
	"Indian",
	"Arabian"
};

#define COLORS_SIZE 7
static char* colors[COLORS_SIZE] = {
	"white",
	"red",
	"blue",
	"cyan",
	"black",
	"yellow",
	"green"
};

#define TIER1_SIZE 5
static char* tier1[TIER1_SIZE] = {
	"cheeky",
	"thong",
	"bikini",
	"tanga",
	"brief",
};

#define TIER2_SIZE 5
static char* tier2[TIER2_SIZE] = {
	"bralette",
	"push-up",
	"strapless",
	"beginner's",
	"bridal",
};

#define TIER3_SIZE 5
static char* tier3[TIER3_SIZE] = {
	"circle",
	"mini",
	"slit",
	"tulle",
	"straight",
};

#define TIER4_SIZE 5
static char* tier4[TIER4_SIZE] = {
	"pantyhose",
	"leggins",
	"stockings",
	"over-the-knee socks",
	"long socks",
};

#define TIER5_SIZE 5
static char* tier5[TIER5_SIZE] = {
	"tank",
	"cami",
	"off-shoulder",
	"crop",
	"strapless",
};

#define TIER6_SIZE 5
static char* tier6[TIER6_SIZE] = {
	"sandals",
	"trainers",
	"platforms",
	"clogs",
	"lita shoes",
};

#define TIER7_SIZE 3
static char* tier7[TIER7_SIZE] = {
	"shorts",
	"jeans",
	"trousers",
};

#define GESTURES_SIZE 3
static char* gestures[GESTURES_SIZE] = {
	"rock",
	"paper",
	"scissors",
};

#define TURNS_COUNT 6

int rnd(int, int);
char* combine(int, char const*, ...);
void swap(char**, char**);
long ntime();

typedef struct {
	int age;
	char* kind;
	char** clothing;
} Person;

Person* new();

int main(void) {
	srand(ntime() * getpid() % time(NULL));

	Person* person = new();
	if (person == NULL) {
		return 1;
	}

	int money = 1000;

	printf("You are playing with a %s %d years old %s %s.\n",
		adjective[rnd(0, ADJECTIVES_SIZE - 1)], person->age, races[rnd(1, RACES_NUM)], person->kind);

	int turns = TURNS_COUNT;

	int p_move, o_move;
	while (turns > 0 && money > 0) {
		printf("\n");
		printf("She is wearing: \n");

		for (int i = 0; i < TURNS_COUNT; i++) {
			if (strlen(person->clothing[i]) > 0) {
				printf("* %s\n", person->clothing[i]);
			}
		}

		o_move = rnd(0, GESTURES_SIZE - 1);
		printf("\n");

		printf("You have $%d.\n", money);
		if (turns < TURNS_COUNT) {
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

		if (turns > 1 && rnd(0, 99) % 2 > 0) {
			swap(&person->clothing[turns - 1], &person->clothing[turns - 2]);
		}

		printf("She is slowly taking off her %s.\n", person->clothing[turns - 1]);
		person->clothing[turns - 1][0] = '\0';

		turns--;
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

	for (int i = 0; i < TURNS_COUNT; i++) {
		free(person->clothing[i]);
	}

	free(person);
	return 0;
}

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

	printf(">>> %s\n", result);
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

int rnd(int const min, int const max) {
	return min + rand() % (max + 1 - min);
}

long ntime() {
	struct timespec ts;

	if (timespec_get(&ts, TIME_UTC) == 0) {
		return UINT64_MAX;
	}

	return ts.tv_nsec;
}

Person* new() {
	Person* person = malloc(sizeof(Person));
	if (!person) {
		goto failed;
	}

	person->age = rnd(MIN_AGE, MAX_AGE);
	person->kind = person->age > 26 ? "woman" : person->age >= 18 ? "girl" : "teenage girl";

	person->clothing = malloc(sizeof(char*) * TURNS_COUNT);
	if (!person->clothing) {
		goto failed;
	}

	person->clothing[0] = combine(3, " ", colors[rnd(0, COLORS_SIZE - 1)], tier1[rnd(0, TIER1_SIZE - 1)], "panties");
	person->clothing[1] = combine(3, " ", colors[rnd(0, COLORS_SIZE - 1)], tier2[rnd(0, TIER2_SIZE - 1)], "bra");

	if (rnd(0, 99) % 2 > 0) {
		person->clothing[2] = combine(3, " ", colors[rnd(0, COLORS_SIZE - 1)], tier3[rnd(0, TIER3_SIZE - 1)], "skirt");
	}else {
		person->clothing[2] = combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier7[rnd(0, TIER7_SIZE - 1)]);
	}

	person->clothing[3] = combine(3, " ", colors[rnd(0, COLORS_SIZE - 1)], tier5[rnd(0, TIER5_SIZE - 1)], "top");
	person->clothing[4] = combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier4[rnd(0, TIER4_SIZE - 1)]);
	person->clothing[5] = combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier6[rnd(0, TIER6_SIZE - 1)]);


	return person;

	failed:
	if (person != NULL) {
		for (int i = 0; i < TURNS_COUNT; i++) {
			free(person->clothing[i]);
		}
	}

	free(person);
	return NULL;
}
