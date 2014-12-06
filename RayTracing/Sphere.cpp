#include "Sphere.h"

#include <cmath>
#include <iostream>

Sphere::Sphere()
{
}

Sphere::Sphere(Vector centre, double radius, double diffuseCoefficient)
{
	_a = radius;
	_b = radius;
	_c = radius;
	_centre = centre;
	_diffuseCoefficient = diffuseCoefficient;
}

Sphere::~Sphere()
{
}

Vector Sphere::SurfaceNormal(Ray incidentRay)
{
	Vector temp(incidentRay.Direction() - Centre());
	Vector normal = temp / temp.Magnitude();
	return normal;
}

double Sphere::Radius()
{
	return _a;
}

double Sphere::Intersection(Ray ray) //Don't need to check for repeated root.  CHECK IF THERE IS A VMIN FIRST.
{
	Vector rayVec = (ray.Direction() - ray.Origin()).UnitVector(); //MAKE SENSE TO DO THIS HERE OR IN THE CALING METHOD?
	
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
	else
	{
		minRoot = -1.0;
	}

	return minRoot;
}
