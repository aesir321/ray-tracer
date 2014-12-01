// Author: Will Parker
#include "Sphere.h"
#include <cmath>
#include <iostream>

Sphere::Sphere()
{

}

Sphere::Sphere(Vector centre, double radius)
{
	_a = radius;
	_b = radius;
	_c = radius;
	_centre = centre;
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

Vector Shape::SurfaceNormal(Ray intersection)
{
	Vector normal;
	
	normal = (intersection - _centre).DivideScalar((intersection - _centre).Magnitude());

	return normal;
}

double Sphere::Radius()
{
	return _a;
}