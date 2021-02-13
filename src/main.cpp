// C++ Standard Library
#include <vector> // for vector
using std::vector;
#include <iostream> // for cout
using std::cout; using std::endl;
#include <cstdlib> // for random numbers
using std::rand; using std::srand;
#include <ctime> // for timing
using std::time;
#include <cmath> // for math
using std::floor; using std::round;
#include <string> // for strings
using std::string;

// Libraries
#include <ncurses.h> // ncurses library

// Our Files
#include "perlin.h"
#include "dijkstra.h"

void dispMaze(WINDOW *window, const vector<vector<double>> &maze);
void dispMaze2(WINDOW *window, const vector<vector<double>> &maze,
		const vector<vector<double>> &costs);
char toGreyscale(double num, double min, double max);

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

	// Getting screen dimensions
	int maxY, maxX;
	getmaxyx(stdscr, maxY, maxX);

	// Printing directions
	mvprintw(0, 0, "Arrow keys to move, q to quit.");
	mvchgat(0, 0, -1, A_REVERSE, 0, NULL);

	// Making our maze window
	WINDOW *mazeWin = newwin(maxY - 1, maxX, 1, 0);

	// Making our Perlin Noise object
	Perlin2D perlin(rand());

	// Making our maze
	vector<vector<double>> maze(50, vector<double>(100, 0));
	for (unsigned int row = 0; row < maze.size(); ++row) {
		for (unsigned int col = 0; col < maze.at(0).size(); ++col) {
			double noise = perlin.noise(row / 10.0, col / 10.0);
			maze.at(row).at(col) = noise;
		}
	}

	// Making our Dijkstra Pathfinding object
	Dijkstra pathfinder(maze);
	pathfinder.pathfind();
	auto costs = pathfinder.getCosts();

	// Drawing our maze
	//dispMaze(mazeWin, maze);
	dispMaze2(mazeWin, maze, costs);
	wrefresh(mazeWin);

	getch(); // (waiting for user input before exiting)

	endwin(); // Exit ncurses mode

	return 0;
}

// Displays a given heightmap in a window
void dispMaze(WINDOW *window, const vector<vector<double>> &maze) {
	// Finding maximum screen dimensions
	int maxY, maxX;
	getmaxyx(window, maxY, maxX);

	// Finding maze dimensions
	int mazeH = maze.size();
	int mazeW = maze.at(0).size();

	// Finding minimum and maximum heights
	double min = maze.at(0).at(0);
	double max = min;
	for (int row = 0; row < mazeH; ++row) {
		for (int col = 0; col < mazeW; ++col) {
			double curr = maze.at(row).at(col);
			if (curr < min) {
				min = curr;
			}
			if (curr > max) {
				max = curr;
			}
		}
	}

	// Displaying the closest pixel in maze at each character on the screen
	for (int y = 0; y < maxY; ++y) {
		for (int x = 0; x < maxX; ++x) {
			int mazeY = floor(((double)y / maxY) * mazeH);
			int mazeX = floor(((double)x / maxX) * mazeW);
			mvwaddch(window, y, x, toGreyscale(maze.at(mazeY).at(mazeX), min, max));
		}
	}
}

void dispMaze2(WINDOW *window, const vector<vector<double>> &maze,
		const vector<vector<double>> &costs) {
	// Finding maze dimensions
	int mazeH = maze.size();
	int mazeW = maze.at(0).size();

	// Finding minimum and maximum heights
	double min = maze.at(0).at(0);
	double max = min;
	for (int row = 0; row < mazeH; ++row) {
		for (int col = 0; col < mazeW; ++col) {
			double curr = maze.at(row).at(col);
			if (curr < min) {
				min = curr;
			}
			if (curr > max) {
				max = curr;
			}
		}
	}

	// Displaying the maze's pixels in greyscale
	for (int y = 0; y < mazeH; ++y) {
		for (int x = 0; x < mazeW; ++x) {
			mvwaddch(window, y, x, toGreyscale(maze.at(y).at(x), min, max));
			int color = (int)floor(costs.at(y).at(x) * 5.0) % 2 + 1;
			mvwchgat(window, y, x, 1, A_BOLD, color, NULL);
		}
	}
}

// Converts a float value in a range to greyscale
char toGreyscale(double num, double min, double max) {
	string greyscale = " -.,~:;+<=%$&#@";

	if (num < min) {num = min;}
	if (num > max) {num = max;}
	double level = (num - min) / (max - min);
	unsigned int pos = round(level * (greyscale.size() - 1));

	return greyscale.at(pos);
}
