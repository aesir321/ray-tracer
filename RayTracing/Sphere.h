// Author: Will Parker
#ifndef SPHERE_H
#define SPHERE_H

#include "Ellipsoid.h"
#include "Vector.h"
#include "Ray.h"

class Sphere : public Ellipsoid
{
public :
	Sphere();
	Sphere(Vector centre, double radius);
	~Sphere();
	double SurfaceArea();
	double Radius();
	void Name();
};

#endif