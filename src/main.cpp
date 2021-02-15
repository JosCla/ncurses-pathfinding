// C++ Standard Library
#include <iostream>
using std::cout; using std::endl;
#include <vector>
using std::vector;
#include <cstdlib>
using std::rand; using std::srand;
#include <ctime>
using std::time;

// Libraries
#include <ncurses.h>

// Our Files
#include "perlin.h"
#include "dijkstra.h"
#include "gui.h"
#include "visuals.h"

int main() {
	// Initialization
	initscr(); // Enter ncurses mode
	cbreak(); // Take one character at a time
	noecho(); // Disable echoing
	keypad(stdscr, true); // Enable special inputs
	curs_set(0); // Hiding the cursor
	refresh(); // (refreshing to make sure child windows are drawn)
	srand(time(nullptr)); // initializing randomization

	// Getting colors ready
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);

	// Getting GUI ready
	GUI ourGUI;
	ourGUI.initWindows();
	ourGUI.setMenuOpen(true);
	ourGUI.boxAll();

	// Drawing the title
	drawTitle(ourGUI.getTitle());

	// Making our Perlin Noise object
	Perlin2D perlin(rand());

	// Making our map
	vector<vector<double>> map(50, vector<double>(160, 0));
	for (unsigned int row = 0; row < map.size(); ++row) {
		for (unsigned int col = 0; col < map.at(0).size(); ++col) {
			double noise = perlin.noise(row / 10.0, col / 10.0);
			map.at(row).at(col) = noise;
		}
	}

	// Making our Dijkstra Pathfinding object
	Dijkstra pathfinder(map);
	pathfinder.pathfind();
	auto costs = pathfinder.getCosts();
	auto dirs = pathfinder.getDirs();

	// Drawing our map
	drawMap(ourGUI.getMap(), map);
	//drawMapCosts(ourGUI.getMap(), map, costs);
	//drawMapDirs(ourGUI.getMap(), map, dirs);
	drawOptPath(ourGUI.getMap(), dirs, 100, 30);
	wrefresh(ourGUI.getMap());

	getch(); // (waiting for user input before exiting)

	endwin(); // Exit ncurses mode

	return 0;
}
