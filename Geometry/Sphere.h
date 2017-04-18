#ifndef SPHERE_H
#define SPHERE_H

#include "Ellipsoid.h"
#include "Vector.h"
#include "Ray.h"
#include "../RGBColour.h"

class Sphere : public Ellipsoid
{
public:

	Sphere();
	Sphere(Vector centre, double radius, double diffuseCoefficient, double reflectionCoefficient, double shininess, RGBColour colour);
	~Sphere();

	Vector SurfaceNormal(Ray ray);
	double Intersection(Ray ray, double epsilon);
	double Radius();
};

#endif
