// Author: Will Parker
#include "Shape.h"
#include <iostream>

Shape::Shape()
{
}

Shape::Shape(Vector centre)
{
	_centre = centre;
}

Shape::~Shape()
{
}

Vector Shape::Centre()
{
	return _centre;
}
