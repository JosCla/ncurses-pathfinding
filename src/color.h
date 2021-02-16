#ifndef COLOR_H
#define COLOR_H
// color.h
// Defines a few ncurses color pairs

// Normal colors
const unsigned int COL_RED = 1;
const unsigned int COL_BLUE = 2;
const unsigned int COL_GREEN = 3;
const unsigned int COL_YELLOW = 4;

// Inverted colors
const unsigned int COL_RED_INV = 5;
const unsigned int COL_BLUE_INV = 6;
const unsigned int COL_GREEN_INV = 7;
const unsigned int COL_YELLOW_INV = 8;

// Sets up colors
void setupColors();

#endif // COLOR_H
