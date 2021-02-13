#ifndef PERLIN_H
#define PERLIN_H
// perlin.h
// Implements Perlin Noise
// Largely based on Ken Perlin's Improved Noise implementation
// Based on: https://adrianb.io/2014/08/09/perlinnoise.html

// C++ Standard Library
#include <vector>

class Perlin2D {
public:
	// Iniitalizes a Perlin Noise generator
	// The given seed is used to create the random lookup table _p (default 0)
	Perlin2D(const unsigned int seed = 0);

	// Gets Perlin Noise at a given point
	double noise(double x, double y);

private:
	// Random lookup table (and respective generation function)
	std::vector<int> _p;
	void _genP();
	
	// Fades smoothly between 0 and 1
	double _fade(double n);

	// Linearly interpolates a and b with weight n
	double _lerp(double n, double a, double b);

	// Pseudo-randomly generates a gradient for given coordinates
	double _grad(int hash, double x, double y);
};

#endif // PERLIN_H
