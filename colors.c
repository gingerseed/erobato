#include "colors.h"
#include "rnd.h"

char const* colors[COLORS_SIZE] = {
	"white",
	"red",
	"blue",
	"cyan",
	"black",
	"yellow",
	"pink",
	"green",
	"grey",
	"turquoise",
	"terracotta",
	"lime",
};

char const* pick_color() {
	return colors[rnd(0, COLORS_SIZE - 1)];
}
