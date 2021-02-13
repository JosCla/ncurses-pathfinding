// perlin.cpp
// Implements perlin.h

// C++ Standard Library
#include <vector>
using std::vector;
#include <cmath>
using std::floor;
#include <cstdlib>
using std::rand; using std::srand;

// Our Files
#include "perlin.h"

Perlin2D::Perlin2D(const unsigned int seed) {
	srand(seed);
	_genP();
}

double Perlin2D::noise(double x, double y) {
	// Coordinates of box bounding x and y
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;
	// Fractional part of x and y
	x -= floor(x);
	y -= floor(y);
	// Fade of x and y's fraction (for smooth interpolation)
	double fx = _fade(x);
	double fy = _fade(y);

	// Finding hashes for the four corners around x and y
	int hx0y0 = _p[_p[X  ]+ Y  ];
	int hx1y0 = _p[_p[X+1]+ Y  ];
	int hx0y1 = _p[_p[X  ]+ Y+1];
	int hx1y1 = _p[_p[X+1]+ Y+1];

	// Then interpolating the random gradients at the corners to find our noise
	double x0 = _lerp(fx, _grad(hx0y0, x  , y  ), _grad(hx1y0, x-1, y  ));
	double x1 = _lerp(fx, _grad(hx0y1, x  , y-1), _grad(hx1y1, x-1, y-1));
	return (_lerp(fy, x0, x1) + 1.0) / 2.0;
}

void Perlin2D::_genP() {
	// Starting _p with integers 0 - 255
	for (int i = 0; i < 256; ++i) {
		_p.push_back(i);
	}

	// Shuffling _p with Fisher-Yates algorithm
	for (int ind = 255; ind > 0; --ind) {
		int switchInd = rand() % (ind + 1);

		int temp = _p.at(ind);
		_p.at(ind) = _p.at(switchInd);
		_p.at(switchInd) = temp;
	}

	// Expanding _p to be itself twice over (to prevent overflows)
	for (int i = 0; i < 256; ++i) {
		_p.push_back(_p.at(i));
	}
}

// Smoothly fades n between 0 and 1
// Returns 6n^5 - 15n^4 + 10n^3
double Perlin2D::_fade(double n) {
	return n * n * n * (n * (n * 6 - 15) + 10);
}

// Linearly interpolates between a and b, with n as the relative weight
// between a and b
double Perlin2D::_lerp(double n, double a, double b) {
	return a + (n * (b - a));
}

// Returns the gradient of a given hash
double Perlin2D::_grad(int hash, double x, double y) {
	double xpart = ((_p.at(hash) / 128.0) - 1.0) * x;
	double ypart = ((_p.at(hash + 1) / 128.0) - 1.0) * y;
	return xpart + ypart;
}
