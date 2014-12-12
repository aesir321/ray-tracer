#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape
{
public :

	Plane();
	Plane(Vector normal, RGBColour colour, double dimension, double diffuseCoefficient, double reflectiveCoefficient, double shininess);
	~Plane();

	double Intersection(Ray ray, double epsilon);
	Vector SurfaceNormal(Ray ray);

private:

	Vector _normal;
	double _dimension;
};

#endif
