#ifndef VISUALS_H
#define VISUALS_H
// visuals.h
// Defines helper functions for drawing various windows

// C++ Standard Library
#include <vector>

// Libraries
#include <ncurses.h>

// Draws the title window
void drawTitle(WINDOW *window);

// Gives a basic greyscale drawing of the map
void drawMap(WINDOW *window, const std::vector<std::vector<double>> &map);

// Draws the map with strips representing different costs
void drawMapCosts(WINDOW *window, const std::vector<std::vector<double>> &map,
		const std::vector<std::vector<double>> &costs);

// Draws the map with different colors representing the optimal direction
// to go in to get to the origin point from each tile
void drawMapDirs(WINDOW *window, const std::vector<std::vector<double>> &map,
		const std::vector<std::vector<int>> &dirs);

// Recursively highlights the optimal path from a tile to the origin point
void drawOptPath(WINDOW *window, const std::vector<std::vector<int>> dirs,
		const int x, const int y);

// Converts a number to greyscale given a minimum and maximum value
char toGreyscale(double num, double min, double max);

// Draws the status window
void drawStatus(WINDOW *window);

#endif // VISUALS_H
