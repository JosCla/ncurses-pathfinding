// dijkstra.cpp
// Implements dijkstra.h

// C++ Standard Library
#include <vector>
using std::vector;
#include <limits>
#include <utility>
using std::pair;
#include <cmath>
using std::fabs;

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
	static const vector<pair<int, int>> dirs = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	while (!_queue.empty()) {
		// Looking at the element at the front of the queue
		auto start = *(_queue.begin());
		double startCost = start.first;
		pair<unsigned int, unsigned int> startCoords = start.second;
		double startHeight = _map.at(startCoords.second).at(startCoords.first);

		// If we've already visited this point, just continue
		if (_visited.count(startCoords)) {
			_queue.erase(_queue.begin());
			continue;
		}

		// Looking at all surrounding points
		for (auto dir : dirs) {
			// Finding the coordinates of the new point
			pair<unsigned int, unsigned int> currCoords = {
				(startCoords.first + dir.first), (startCoords.second + dir.second)
			};

			// Making sure the new point is not out of bounds
			// (notice that the unsigned comparison also ensures non-negative)
			if (currCoords.first >= _width || currCoords.second >= _height) {
				continue;
			}

			// Finding the new cost
			double currHeight = _map.at(currCoords.second).at(currCoords.first);
			double currCost = startCost + fabs(currHeight - startHeight);
			
			// If the new cost is the best we've found for this point,
			// modify the cost in _costs and add the point to the queue
			if (currCost < _costs.at(currCoords.second).at(currCoords.first)) {
				_costs.at(currCoords.second).at(currCoords.first) = currCost;
				_queue.insert({currCost, currCoords});
				// TODO: optimal direction
			}
		}

		// Adding the current point to the _visited set
		_visited.insert(startCoords);
		// Popping the now traversed item from the front of the _queue
		_queue.erase(_queue.begin());
	}
}

void Dijkstra::resetPath() {
	// Resetting optimal costs and directions
	_costs = vector<vector<double>>(_height, 
			vector<double>(_width, std::numeric_limits<double>::infinity()));
	_dirs = vector<vector<char>>(_height, vector<char>(_width, ' '));

	// Putting the relevant starting node into an emptied queue
	_queue.clear();
	_queue.insert({0.0, {_startX, _startY}});
	_visited.clear();
	// and making the starting node have cost 0.0
	_costs.at(_startY).at(_startX) = 0.0;
}

void Dijkstra::setMap(const vector<vector<double>> &map) {
	// Resetting the map and relevant dimensions
	_map = map;
	_height = _map.size();
	_width = _map.at(0).size();

	// Resetting pathfinding data
	resetPath();

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

	// Resetting path data, since _costs and _dirs are now outdated
	resetPath();
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

const vector<vector<double>>& Dijkstra::getCosts() {
	return _costs;
}
