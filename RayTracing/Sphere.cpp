// Author: Will Parker
#include "Sphere.h"
#include <cmath>
#include <iostream>

Sphere::Sphere()
{

}

Sphere::Sphere(double radius)
{
	_a = radius;
	_b = radius;
	_c = radius;
}

Sphere::~Sphere()
{
}

double Sphere::SurfaceArea() // Use this one as the ellipsoid is an approximation.
{
	return 4.0 * _PI * pow(_a, 2);
}

void Sphere::Name()
{
	std::cout << "Sphere" << std::endl;
}