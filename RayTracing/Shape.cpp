#include "Shape.h"
#include <iostream>

Shape::Shape()
{
}

Shape::Shape(Vector centre, RGBColour colour)
{
	_centre = centre;
	_colour = colour;
}

Shape::~Shape()
{
}

Vector Shape::Centre()
{
	return _centre;
}

void Shape::SetColour(RGBColour colour)
{
	_colour = colour;
}

RGBColour Shape::Colour()
{
	return _colour;
}
