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
#include "color.h"

int main() {
	// Initialization
	initscr(); // Enter ncurses mode
	cbreak(); // Take one character at a time
	noecho(); // Disable echoing
	keypad(stdscr, true); // Enable special inputs
	//curs_set(0); // Hiding the cursor
	refresh(); // (refreshing to make sure child windows are drawn)
	srand(time(nullptr)); // initializing randomization

	// Getting colors ready
	start_color();
	setupColors();

	// Getting GUI ready
	GUI ourGUI;
	ourGUI.initWindows();
	ourGUI.setMenuOpen(true);
	ourGUI.boxAll();

	// Drawing the title
	drawTitle(ourGUI.getTitle());

	// Drawing the status
	drawStatus(ourGUI.getStatus());

	// Making our Perlin Noise object
	Perlin2D perlin(rand());

	// Making our map
	vector<vector<double>> map(160, vector<double>(160, 0));
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
	//drawOptPath(ourGUI.getMap(), dirs, 100, 30);
	wrefresh(ourGUI.getMap());

	// Getting user cursor ready
	int cursX(0), cursY(1);
	move(cursY, cursX);

	// Main game loop
	bool exit = false;
	while (exit == false) {
		// Getting user input
		int userInput = getch();
		switch (userInput) {
			case KEY_UP:
				{
				if (cursY > 0) {
					--cursY;
					move(cursY, cursX);
				}
				}
				break;
			case KEY_DOWN:
				{
				int maxY, maxX;
				getmaxyx(ourGUI.getMap(), maxY, maxX);
				if (cursY < (maxY)) {
					++cursY;
					move(cursY, cursX);
				}
				}
				break;
			case KEY_LEFT:
				{
				if (cursX > 0) {
					--cursX;
					move(cursY, cursX);
				}
				}
				break;
			case KEY_RIGHT:
				{
				int maxY, maxX;
				getmaxyx(ourGUI.getMap(), maxY, maxX);
				if (cursX < (maxX - 1)) {
					++cursX;
					move(cursY, cursX);
				}
				}
				break;
				
			case 'p':
				drawOptPath(ourGUI.getMap(), dirs, cursX, cursY - 1);
				break;
			case 'o':
				drawMap(ourGUI.getMap(), map);
				break;

			case 'q':
				exit = true;
				break;
		}

		// Refreshing the screen
		wrefresh(ourGUI.getMap());
		move(cursY, cursX);
	}

	endwin(); // Exit ncurses mode

	return 0;
}
