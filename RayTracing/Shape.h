#ifndef SHAPE_H
#define SHAPE_H

#include "Vector.h"
#include "Ray.h"
#include "EasyBMP.h"

class Shape
{
public :
	Shape();
	Shape(Vector centre, RGBApixel colour);
	~Shape();
	virtual double Volume() = 0;
	virtual double SurfaceArea() = 0;
	virtual void Name() = 0;
	virtual Vector SurfaceNormal(Ray ray) = 0;
	virtual double Intersection(Ray ray) = 0;
	Vector Centre();
	void SetColour(RGBApixel colour);
	RGBApixel Colour();
	
protected :
	Vector _centre;
	double _refractiveIndex;
	double _reflectiveIndex;
	RGBApixel _colour;
};
#endif
