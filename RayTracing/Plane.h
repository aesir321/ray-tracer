#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"

class Plane : public Shape
{
public :
	Plane();
	Plane(Vector normal, RGBColour colour, double dimension);
	~Plane();
	double Intersection(Ray ray);
	Vector SurfaceNormal(Ray ray);

private:
	Vector _normal;
	double _dimension; //Distance from centre of plane to centre of scene?
};

#endif