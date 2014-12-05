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

Vector Sphere::SurfaceNormal(Ray incidentRay)
{
	Vector temp(incidentRay.Direction() - Centre());
	double mag = temp.Magnitude();
	Vector normal = (temp).DivideScalar(mag); // overload /
	return normal;
}

double Sphere::Radius()
{
	return _a;
}

double Sphere::Intersection(Ray ray) //Don't need to check for repeated root.  CHECK IF THERE IS A VMIN FIRST.
{
	Vector rayVec = (ray.Direction() - ray.Origin()).UnitVector();
	
	double a = rayVec.ScalarProduct(rayVec);
	Vector temp = ray.Origin() - Centre();
	double b = rayVec.ScalarProduct(temp);
	double c = temp.ScalarProduct(temp) - pow(Radius(), 2);

	double root1 = 0.0;
	double root2 = 0.0;
	double discriminant = 0.0;
	double minRoot = 0.0;

	discriminant = pow(b, 2) - (c);

	if (discriminant > 0)
	{
		root1 = (-b + sqrt(discriminant));
		root2 = (-b - sqrt(discriminant));

		if (root1 <= 0.0 && root2 <= 0.0)
		{
			minRoot = -1.0;
		}
		else if (root1 > 0.0 && root2 > 0.0)
		{
			if (root1 < root2)
			{
				minRoot = root1;
			}
			else if (root2 < root1)
			{
				minRoot = root2;
			}
		}
		else if (root1 > 0.0 && root2 < 0.0)
		{
			minRoot = root1;
		}
		else if (root2 > 0.0 && root1 < 0.0)
		{
			minRoot = root2;
		}
	}
	else if (discriminant == 0) //Don't think this is necessary.
	{
		root1 = (b * sqrt(discriminant)) / (2 * a);
		if (root1 > 0)
		{
			minRoot = root1;
		}
		else
		{
			minRoot = -1.0;
		}
	}
	else
	{
		minRoot = -1.0;
	}
	return minRoot;
}
