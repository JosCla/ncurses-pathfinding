// dijkstra.cpp
// Implements dijkstra.h

// C++ Standard Library
#include <vector>
using std::vector;

// Our Files
#include "dijkstra.h"

Dijkstra::Dijkstra(const vector<vector<double>> &map) {
	// Setting up a few default values
	_startX = 0; _startY = 0;
	_endX = 0; _endY = 0; _stopAtEnd = false;

	// Setting up the map
	setMap(map);
}

void Dijkstra::pathfind() {
	// TODO
}

void Dijkstra::setMap(const vector<vector<double>> &map) {
	// Resetting the map and relevant dimensions
	_map = map;
	_height = _map.size();
	_width = _map.at(0).size();

	// Resetting _costs and _dirs
	// TODO: put in a separate function so setStart can call this too
	_costs = vector<vector<double>>(_height, vector<double>(_width, 0.0));
	_dirs = vector<vector<char>>(_height, vector<char>(_width, ' '));

	// Defaulting start/end coordinates to (0,0) if invalid
	setStart(_startX, _startY);
	setEnd(_endX, _endY);
}

void Dijkstra::setStart(unsigned int startX, unsigned int startY) {
	// Setting
	_startX = startX;
	_startY = startY;

	// Validating
	if (_startX >= _width || _startX < 0) {_startX = 0;}
	if (_startY >= _height || _startY < 0) {_startY = 0;}
}

void Dijkstra::setEnd(unsigned int endX, unsigned int endY) {
	// Setting
	_endX = endX;
	_endY = endY;

	// Validating
	if (_endX >= _width || _endX < 0) {_endX = 0;}
	if (_endY >= _height || _endY < 0) {_endY = 0;}
}

void Dijkstra::setStopAtEnd(bool stop) {
	_stopAtEnd = stop;
}
