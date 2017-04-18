#ifndef ELLIP_H
#define ELLIP_H
#include "Shape.h"

class Ellipsoid : public Shape
{
public :
	Ellipsoid();
	Ellipsoid(double a, double b, double c);
	~Ellipsoid();
	Vector SurfaceNormal(Ray ray);
	double Intersection(Ray ray, double epsilon);

protected :
	double _a;
	double _b;
	double _c;
	const double _P = 1.6075;
	const double _PI = 3.1415926535897932384626433832795028841971693993751058;
};
#endif
