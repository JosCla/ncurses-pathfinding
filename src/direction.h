#ifndef DIRECTION_H
#define DIRECTION_H
// direction.h
// Defines a few helper functions for directional movement

// C++ Standard Library
#include <utility>

// Converts a pair displacement to an integer rotation
int dirToInt(const std::pair<int, int> &dir);
// Converts back from an integer rotation to a pair displacement
std::pair<int, int> intToDir(const int dir);

// Reverses a given integer rotation
int reverseDir(const int dir);

#endif // DIRECTION_H
