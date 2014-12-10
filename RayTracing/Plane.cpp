#include "Plane.h"


Plane::Plane()
{

}

Plane::Plane(Vector normal, RGBColour colour, double dimension, double diffuseCoefficient, double reflectiveCoefficient, double shininess)
{
	_normal = normal;
	_colour = colour;
	_dimension = dimension;
	_diffuseCoefficient = diffuseCoefficient;
	_reflectionCoefficient = reflectiveCoefficient;
	_shininess = shininess;
}

Plane::~Plane()
{
}


double Plane::Intersection(Ray ray, double epsilon)
{
	double intersection = 0.0;
	double a = ray.Direction().UnitVector().ScalarProduct(_normal);

	if (a == 0) // parallel to plane
	{
		intersection = -1.0;
	}
	else
	{
		intersection = _normal.ScalarProduct(ray.Origin() * -1 + _dimension) / a;

	}

	return intersection;
}

Vector Plane::SurfaceNormal(Ray ray)
{
	return _normal; //Plane has the same surface normal over the whole plane.
}