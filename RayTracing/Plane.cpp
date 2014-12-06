#include "Plane.h"
#include <fstream>

Plane::Plane()
{
}

Plane::Plane(Vector normal, RGBColour colour, double dimension)
{
	_normal = normal;
	_colour = colour;

	std::fstream file;
	file.open("log.txt", std::ios_base::app);
	file << "setting colour to: " << _colour.Red() << ", " << _colour.Green() << ", " << _colour.Blue() << std::endl;

	file.close();

	_dimension = dimension; //distance from origin to centre of plane.
}

Plane::~Plane()
{
}


double Plane::Intersection(Ray ray)
{
	
	double intersection = 0.0;
	double a = ray.Direction().UnitVector().ScalarProduct(_normal);

	if (a == 0) // parallel to plane
	{
		intersection = -1.0;
	}
	else
	{
		intersection = _normal.ScalarProduct(ray.Origin() + _normal * (-1 * _dimension)) / a;

	}
	
	/*std::fstream file;
	file.open("log.txt", std::ios_base::app);
	file << "ray origin: " << ray.Origin().GetFirstComponent() << ", " << ray.Origin().GetSecondComponent() << ", " << ray.Origin().GetThirdComponent() << std::endl;
	file << "ray direction: " << ray.Direction().GetFirstComponent() << ", " << ray.Direction().GetSecondComponent() << ", " << ray.Direction().GetThirdComponent() << std::endl;
	file << "surface normal: " << _normal.GetFirstComponent() << ", " << _normal.GetSecondComponent() << ", " << _normal.GetThirdComponent() << std::endl;
	file << "dimension: " << _dimension << std::endl;
	file << "a: " << a << std::endl;
	file << "intersection: " << intersection << std::endl;
	file << "colour: " << _colour.Red() << ", " << _colour.Green() << ", " << _colour.Blue() << std::endl;
	file << "------------------------------------------" << std::endl;
	file.close();*/

	return intersection;
}

Vector Plane::SurfaceNormal(Ray ray)
{
	return _normal; //Plane has the same surface normal over the whole plane.
}