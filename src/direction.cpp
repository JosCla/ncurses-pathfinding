// direction.cpp
// Implements direction.h

// C++ Standard Library
#include <utility>
using std::pair;

// Our Files
#include "direction.h"

// Converts a pair displacement to an integer rotation
int dirToInt(const pair<int, int> &dir) {
	int hash = (dir.first * 3) + dir.second;
	
	// Made to handle ({-1, 0, 1}, {-1, 0, 1}) displacements
	// Return value represents rotation in radians with [0,7] -> [0,7pi/8]
	switch (hash) {
		case 3:
			return 0;
		case 2:
			return 1;
		case -1:
			return 2;
		case -4:
			return 3;
		case -3:
			return 4;
		case -2:
			return 5;
		case 1:
			return 6;
		case 4:
			return 7;
		default:
			return 0;
	}
}

// Converts back from an integer rotation to a pair displacement
pair<int, int> intToDir(const int dir) {
	// Made to handle ({-1, 0, 1}, {-1, 0, 1}) displacements
	// Maps [0,7] -> [0,7pi/8]
	switch (dir) {
		case 0:
			return pair<int, int>( 1,  0);
		case 1:
			return pair<int, int>( 1, -1);
		case 2:
			return pair<int, int>( 0, -1);
		case 3:
			return pair<int, int>(-1, -1);
		case 4:
			return pair<int, int>(-1,  0);
		case 5:
			return pair<int, int>(-1,  1);
		case 6:
			return pair<int, int>( 0,  1);
		case 7:
			return pair<int, int>( 1,  1);
		default:
			return pair<int, int>( 0,  0);
	}
}

// Reverses a given integer rotation
int reverseDir(const int dir) {
	// Made to handle ({-1, 0, 1}, {-1, 0, 1}) displacements
	return (dir + 4) % 8;
}
