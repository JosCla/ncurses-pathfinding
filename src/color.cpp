// color.cpp
// Implements color.h

// Libraries
#include <ncurses.h>

// Our Files
#include "color.h"

void setupColors() {
	// Normal colors
	init_pair(COL_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COL_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COL_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COL_YELLOW, COLOR_YELLOW, COLOR_BLACK);

	// Inverted colors
	init_pair(COL_RED_INV, COLOR_WHITE, COLOR_RED);
	init_pair(COL_BLUE_INV, COLOR_WHITE, COLOR_BLUE);
	init_pair(COL_GREEN_INV, COLOR_WHITE, COLOR_GREEN);
	init_pair(COL_YELLOW_INV, COLOR_WHITE, COLOR_YELLOW);
}
