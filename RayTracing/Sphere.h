// Author: Will Parker
#ifndef SPHERE_H
#define SPHERE_H
#include "Ellipsoid.h"
#include "Vector"

class Sphere : public Ellipsoid
{
public :
	Sphere();
	Sphere(double radius);
	~Sphere();
	double SurfaceArea();
	void Name();
};
#endif