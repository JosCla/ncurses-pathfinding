// visuals.cpp
// Implements visuals.h

// C++ Standard Library
#include <vector>
using std::vector;
#include <cmath>
using std::floor; using std::round;
#include <string>
using std::string;
#include <utility>
using std::pair;

// Libraries
#include <ncurses.h>

// Our Files
#include "visuals.h"
#include "direction.h"

// Gives a basic greyscale drawing of the map
void drawMap(WINDOW *window, const vector<vector<double>> &map) {
	// Finding map dimensions
	int mapH = map.size();
	int mapW = map.at(0).size();

	// Finding minimum and maximum heights
	double min = map.at(0).at(0);
	double max = min;
	for (int row = 0; row < mapH; ++row) {
		for (int col = 0; col < mapW; ++col) {
			double curr = map.at(row).at(col);
			if (curr < min) {
				min = curr;
			}
			if (curr > max) {
				max = curr;
			}
		}
	}

	// Displaying the closest pixel in map at each character on the screen
	for (int y = 0; y < mapH; ++y) {
		for (int x = 0; x < mapW; ++x) {
			mvwaddch(window, y, x, toGreyscale(map.at(y).at(x), min, max));
		}
	}
}

// Draws the map with strips representing different costs
void drawMapCosts(WINDOW *window, const vector<vector<double>> &map,
		const vector<vector<double>> &costs) {
	// Drawing the map normally
	drawMap(window, map);

	// Finding map dimensions
	int mapH = map.size();
	int mapW = map.at(0).size();

	// Coloring each tile according to its cost
	for (int y = 0; y < mapH; ++y) {
		for (int x = 0; x < mapW; ++x) {
			int color = (int)floor(costs.at(y).at(x) * 5.0) % 2 + 1;
			mvwchgat(window, y, x, 1, A_BOLD, color, NULL);
		}
	}
}

// Draws the map with different colors representing the optimal direction
// to go in to get to the origin point from each tile
void drawMapDirs(WINDOW *window, const vector<vector<double>> &map,
		const vector<vector<int>> &dirs) {
	// Drawing the map normally
	drawMap(window, map);

	// Finding map dimensions
	int mapH = map.size();
	int mapW = map.at(0).size();

	// Coloring each tile according to its optimal direction
	for (int y = 0; y < mapH; ++y) {
		for (int x = 0; x < mapW; ++x) {
			int color = dirs.at(y).at(x) / 2 + 1;
			mvwchgat(window, y, x, 1, A_BOLD, color, NULL);
		}
	}
}

// Recursively highlights the optimal path from a tile to the origin point
void drawOptPath(WINDOW *window, const vector<vector<int>> dirs,
		const int x, const int y) {
	mvwchgat(window, y, x, 1, A_REVERSE, 3, NULL);

	if (x != 0 || y != 0) {
		pair<int, int> dir = intToDir(dirs.at(y).at(x));
		drawOptPath(window, dirs, x + dir.first, y + dir.second);
	}
}

// Converts a number to greyscale given a minimum and maximum value
char toGreyscale(double num, double min, double max) {
	string greyscale = " .,-~:;+<=%$&#@";

	if (num < min) {num = min;}
	if (num > max) {num = max;}
	double level = (num - min) / (max - min);
	unsigned int pos = round(level * (greyscale.size() - 1));

	return greyscale.at(pos);
}
