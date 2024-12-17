#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
	"Arabic"
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

#define GESTURES_SIZE 3
static char* gestures[GESTURES_SIZE] = {
	"rock",
	"paper",
	"scissors",
};

#define TURNS_COUNT 6

int rnd(int, int);
char* combine(int, char const*, ...);
void swap(char*, char*);

void main(void) {
	srand(time(NULL));

	int money = 1000;
	int const age = rnd(MIN_AGE, MAX_AGE);
	const char* type = age > 26 ? "woman" : "girl";

	printf("Hello, adventurer!\n");
	printf("You are playing with a %s %d years old %s %s.\n",
		adjective[rnd(0, ADJECTIVES_SIZE - 1)], age,
		races[rnd(1, RACES_NUM)], type);

	int turns = TURNS_COUNT;
	char* clothing[TURNS_COUNT] = {
		combine(3, " ", colors[rnd(0, COLORS_SIZE - 1)], tier1[rnd(0, TIER1_SIZE - 1)], "panties"),
		combine(3, " ", colors[rnd(0, COLORS_SIZE - 1)], tier2[rnd(0, TIER2_SIZE - 1)], "bra"),
		combine(3, " ", colors[rnd(0, COLORS_SIZE - 1)], tier3[rnd(0, TIER3_SIZE - 1)], "skirt"),
		combine(3, " ", colors[rnd(0, COLORS_SIZE - 1)], tier5[rnd(0, TIER5_SIZE - 1)], "top"),
		combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier4[rnd(0, TIER4_SIZE - 1)]),
		combine(2, " ", colors[rnd(0, COLORS_SIZE - 1)], tier6[rnd(0, TIER6_SIZE - 1)]),
	};

	int p_move, o_move;
	while (turns > 0 && money > 0) {
		printf("\n");
		printf("She is wearing: \n");

		for (int i = 0; i < TURNS_COUNT; i++) {
			if (strlen(clothing[i]) > 0) {
				printf("* %s\n", clothing[i]);
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
			swap(clothing[turns - 1], clothing[turns - 2]);
		}

		printf("She is slowly taking off her %s.\n", clothing[turns - 1]);
		clothing[turns - 1][0] = '\0';

		turns--;
		continue;

	lose:
		printf("You lost! I will cost you $100.\n");
		money -= 100;
	}

	if (money > 0) {
		printf("\"Oh, you nailed it!\" - said the %s sitting totally naked in the %s pose.\n",
			type, adjective[rnd(0, ADJECTIVES_SIZE - 1)]);
	} else {
		printf("\"Such a loser\" - the %s is laughing at you!\n", type);
	}

	for (int i = 0; i < TURNS_COUNT; i++) {
		free(clothing[i]);
	}
}

char* combine(int const count, char const* sp, ...) {
	long unsigned size = 1;
	char* result = calloc(size, sizeof(char*));

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
			return NULL;
		}

		result = n;
		if (i > 0) {
			strcat(result, sp);
		}

		strcat(result, frn);
	}

	va_end(p);
	return result;
}


void swap(char* a, char* b) {
	if (a == b) {
		return;
	}

	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

int rnd(int const min, int const max) {
	return min + rand() % (max + 1 - min);
}
