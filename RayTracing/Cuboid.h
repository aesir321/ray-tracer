// Author: Will Parker
#ifndef CUBOID_H
#define CUBOID_H

#include "Shape.h"

class Cuboid : public Shape
{
public :
	Cuboid();
	Cuboid(double side1, double side2, double side3);
	~Cuboid();
	double SurfaceArea();
	double Volume();
	void Name();

private :
	double _side1;
	double _side2;
	double _side3;

};
#endif