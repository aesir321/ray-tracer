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

Vector Ellipsoid::SurfaceNormal(Ray ray)
{
  return Vector();
}

double Ellipsoid::Intersection(Ray ray)
{
	return 0.0;
}
