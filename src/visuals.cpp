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
#include <sstream>
using std::istringstream;

// Libraries
#include <ncurses.h>

// Our Files
#include "visuals.h"
#include "direction.h"
#include "color.h"

// Draws the title window
void drawTitle(WINDOW *window) {
	// Clearing the window
	wclear(window);

	// Printing the title section
	mvwprintw(window, 0, 0, "ncurses-pathfinding | (c)ontrols (o)ptions (q)uit");
	mvwchgat(window, 0, 0, -1, A_REVERSE, 0, NULL);

	// Refreshing the window
	wrefresh(window);
}

// Gives a basic greyscale drawing of the map
void drawMap(WINDOW *window, const vector<vector<double>> &map) {
	// Clearing the window
	wclear(window);

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
	// Clearing the window
	wclear(window);

	// Drawing the map normally
	drawMap(window, map);

	// Finding map dimensions
	int mapH = map.size();
	int mapW = map.at(0).size();

	// Coloring each tile according to its cost
	for (int y = 0; y < mapH; ++y) {
		for (int x = 0; x < mapW; ++x) {
			int color;
			if ((int)floor(costs.at(y).at(x) * 5.0) % 2 == 0) {
				color = COL_RED;
			} else {
				color = COL_BLUE;
			}
			mvwchgat(window, y, x, 1, A_BOLD, color, NULL);
		}
	}
}

// Draws the map with different colors representing the optimal direction
// to go in to get to the origin point from each tile
void drawMapDirs(WINDOW *window, const vector<vector<double>> &map,
		const vector<vector<int>> &dirs) {
	// Clearing the window
	wclear(window);

	// Drawing the map normally
	drawMap(window, map);

	// Finding map dimensions
	int mapH = map.size();
	int mapW = map.at(0).size();

	// Coloring each tile according to its optimal direction
	for (int y = 0; y < mapH; ++y) {
		for (int x = 0; x < mapW; ++x) {
			int color;
			switch (dirs.at(y).at(x)) {
				case 0:
					color = COL_RED;
					break;
				case 2:
					color = COL_BLUE;
					break;
				case 4:
					color = COL_GREEN;
					break;
				case 6:
					color = COL_YELLOW;
					break;
				default:
					color = COL_RED;
			}
			mvwchgat(window, y, x, 1, A_BOLD, color, NULL);
		}
	}
}

// Recursively highlights the optimal path from a tile to the origin point
void drawOptPath(WINDOW *window, const vector<vector<int>> dirs,
		const int x, const int y, const int endX, const int endY) {
	mvwchgat(window, y, x, 1, A_REVERSE, 3, NULL);

	if (x != endX || y != endY) {
		pair<int, int> dir = intToDir(dirs.at(y).at(x));
		drawOptPath(window, dirs, x + dir.first, y + dir.second, endX, endY);
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

// Draws a Dijkstra pathfinding object
void drawDijkstra(WINDOW *window, const Dijkstra &dijkstra) {
	// Highlighting all queue points in blue
	auto pointQueue = dijkstra.getQueue();
	for (auto point : pointQueue) {
		mvwchgat(window, point.second.second, point.second.first, 1, 
				A_BOLD | A_REVERSE, COL_BLUE, NULL);
	}

	// Coloring all visited squares blue
	auto visited = dijkstra.getVisited();
	for (auto point : visited) {
		mvwchgat(window, point.second, point.first, 1, A_BOLD, COL_BLUE, NULL);
	}

	// Getting the next point in the queue, drawing opt path to start
	if (!pointQueue.empty()) {
		auto nextPoint = *(pointQueue.begin());
		auto start = dijkstra.getStart();
		drawOptPath(window, dijkstra.getDirs(), nextPoint.second.first,
				nextPoint.second.second, start.first, start.second);
		mvwchgat(window, nextPoint.second.second, nextPoint.second.first, 1,
				A_BOLD | A_REVERSE, COL_YELLOW, NULL);
	}
}

// Draws the controls window
void drawControls(WINDOW *window) {
	int maxY, maxX;
	getmaxyx(window, maxY, maxX);

	string controls = "arrow keys: move cursor\n";
	controls += "s: set start point (cost zero)\n";
	controls += "p: mark optimal path from start to cursor\n";
	controls += "d: delete all marked paths\n";
	controls += "\n";
	//controls += "h: hide controls";

	int y = 1;
	int x = 1;
	for (char c : controls) {
		// Accounting for newlines
		if (c == '\n') {
			++y;
			x = 1;
			continue;
		}

		// Adding current character
		mvwaddch(window, y, x, c);

		// Moving cursor to next character
		++x;
		if (x > (maxX - 2)) {
			++y;
			x = 1;
		}
	}

	wrefresh(window);
}

// Draws the status window
void drawStatus(WINDOW *window) {
	// Clearing the window
	wclear(window);

	// Drawing the status
	mvwchgat(window, 0, 0, -1, A_REVERSE, 0, NULL);
	
	// Refreshing the window
	wrefresh(window);
}
