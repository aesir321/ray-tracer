#ifndef SPHERE_H
#define SPHERE_H

#include "Ellipsoid.h"
#include "Vector.h"
#include "Ray.h"

class Sphere : public Ellipsoid
{
public :
	Sphere();
	Sphere(Vector centre, double radius, double diffuseCoefficient, double reflectionCoefficient, double shininess);
	~Sphere();
	Vector SurfaceNormal(Ray ray);
	double Intersection(Ray ray);
	double Radius();
};

#endif
