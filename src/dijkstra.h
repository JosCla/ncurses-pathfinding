#ifndef DIJKSTRA_H
#define DIJKSTRA_H
// dijkstra.h
// Implements Dijkstra's pathfinding algorithm

// C++ Standard Library
#include <string>
#include <vector>
#include <list>
#include <utility>

class Dijkstra {
public:
	// Initializes a Dijkstra pathfinder with a given cost map
	// The starting point of cost 0 can also be specified
	Dijkstra(const std::vector<std::vector<double>> &map);

	// Pathfinds throughout the entire map, finding the optimal cost
	// of reaching every point
	void pathfind();

	// Sets the map
	void setMap(const std::vector<std::vector<double>> &map);

	// Sets the starting coordinates
	void setStart(unsigned int startX, unsigned int startY);

	// Sets the ending coordinates
	void setEnd(unsigned int endX, unsigned int endY);
	void setStopAtEnd(bool stop);

private:
	// The cost map to be traversed
	std::vector<std::vector<double>> _map;
	unsigned int _width;
	unsigned int _height;

	// The cost of moving to each point from the starting points
	// (starts as 0.0 for all points)
	std::vector<std::vector<double>> _costs;

	// The direction to move from a certain point in order to optimally
	// move back to (_startX, _startY). (starts as ' ' for all points)
	std::vector<std::vector<char>> _dirs;

	// The starting point of cost 0
	unsigned int _startX;
	unsigned int _startY;
	
	// The ending point (pathfinding will optionally stop upon reaching it)
	unsigned int _endX;
	unsigned int _endY;
	bool _stopAtEnd;

	// The queue of points to be checked by the pathfinding algorithm
	// TODO: this wouldn't work, actually
	std::list<std::pair<unsigned int, unsigned int>> _queue;
};

#endif // DIJKSTRA_H