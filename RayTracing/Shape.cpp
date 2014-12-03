#include "Shape.h"
#include <iostream>

Shape::Shape()
{
}

Shape::Shape(Vector centre, RGBApixel colour)
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

void Shape::SetColour(RGBApixel colour)
{
	_colour = colour;
}

RGBApixel Shape::Colour()
{
	return _colour;
}
