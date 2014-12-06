#include "Shape.h"
#include <iostream>

Shape::Shape()
{
}

Shape::Shape(Vector centre, RGBColour colour, double diffuseCoefficient, double reflectionCoefficient)
{
	_centre = centre;
	_colour = colour;
	_diffuseCoefficient = diffuseCoefficient;
	_reflectionCoefficient = reflectionCoefficient;
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

double Shape::DiffuseCoefficient()
{
	return _diffuseCoefficient;
}

double Shape::ReflectionCoefficient()
{
	return _reflectionCoefficient;
}
