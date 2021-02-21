// dijkstra.cpp
// Implements dijkstra.h

// C++ Standard Library
#include <vector>
using std::vector;
#include <limits>
#include <utility>
using std::pair; using std::make_pair;
#include <cmath>
using std::fabs;
#include <set>
using std::set;

// Our Files
#include "dijkstra.h"
#include "direction.h"

Dijkstra::Dijkstra(const vector<vector<double>> &map) {
	// Setting up a few default values
	_startX = 0; _startY = 0;
	_endX = 0; _endY = 0; _stopAtEnd = false;

	// Setting up the map
	setMap(map);
}

void Dijkstra::pathfind() {
	while (step()) {}
}

bool Dijkstra::step() {
	// (directions for pathfinding)
	static const vector<pair<int, int>> dirs = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	while (!_queue.empty()) {
		// Trying to find a new point to pathfind to
		pair<unsigned int, unsigned int> startCoords = _queue.begin()->second;
		if (_visited.count(startCoords) == 0) {
			break;
		} else {
			_queue.erase(_queue.begin());
		}
	}

	if (_queue.empty()) {
		// No more points to pathfind to! Returning false.
		return false;
	}

	// If we've found a new point, visit it
	auto start = *(_queue.begin());
	double startCost = start.first;
	pair<unsigned int, unsigned int> startCoords = start.second;
	double startHeight = _map.at(startCoords.second).at(startCoords.first);

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
			_dirs.at(currCoords.second).at(currCoords.first) =
				reverseDir(dirToInt(dir));
			_queue.insert({currCost, currCoords});
		}
	}

	// Adding the current point to the _visited set
	_visited.insert(startCoords);
	// Popping the now traversed item from the front of the _queue
	_queue.erase(_queue.begin());

	// Returning true to indicate successful pathfinding step
	return true;
}

void Dijkstra::resetPath() {
	// Resetting optimal costs and directions
	_costs = vector<vector<double>>(_height, 
			vector<double>(_width, std::numeric_limits<double>::infinity()));
	_dirs = vector<vector<int>>(_height, vector<int>(_width, 0));

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
pair<unsigned int, unsigned int> Dijkstra::getStart() {
	return make_pair(_startX, _startY);
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

const vector<vector<int>>& Dijkstra::getDirs() {
	return _dirs;
}

const set<pair<double, pair<unsigned int, unsigned int>>>& 
	Dijkstra::getQueue() {
	return _queue;
}

const set<pair<unsigned int, unsigned int>>& Dijkstra::getVisited() {
	return _visited;
}
