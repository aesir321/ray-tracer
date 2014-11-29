// Author: Will Parker
#ifndef SHAPE_H
#define SHAPE_H

#include "Vector.h"
class Shape
{
public :
	Shape();
	~Shape();
	virtual double Volume() = 0;
	virtual double SurfaceArea() = 0;
	virtual void Name() = 0;
	void PrintShapeStats(Shape &shape);
	Vector SurfaceNormal(Shape &shape);
	
private :
	Vector _centre;
	double _refractiveIndex;
	double _reflectiveIndex;
};
#endif