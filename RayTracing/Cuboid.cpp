#include "Cuboid.h"
#include <iostream>

Cuboid::Cuboid()
{
	_side1 = 0.0;
	_side2 = 0.0;
	_side3 = 0.0;
}

Cuboid::Cuboid(double side1, double side2, double side3)
{
	_side1 = side1;
	_side2 = side2;
	_side3 = side3;
}

Cuboid::~Cuboid()
{
}