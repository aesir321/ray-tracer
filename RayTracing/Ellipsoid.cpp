// Author: Will Parker
#include "Ellipsoid.h"
#include <cmath>
#include <iostream>

Ellipsoid::Ellipsoid()
{
	_a = 1.0;
	_b = 1.0;
	_c = 1.0;
}

Ellipsoid::Ellipsoid(double a, double b, double c)
{
	_a = a;
	_b = b;
	_c = c;
}

Ellipsoid::~Ellipsoid()
{
}

double Ellipsoid::SurfaceArea()
{
	return 4 * _PI * pow((pow(_a, _P) * pow(_b, _P) + pow(_a, _P) * pow(_c, _P) + pow(_b, _P) * pow(_c, _P)) / 3, 1 / _P);
}

double Ellipsoid::Volume()
{
	return 4.0 * _PI * _a * _b * _c / 3.0;
}

void Ellipsoid::Name()
{
	std::cout << "Ellipsoid" << std::endl;
}