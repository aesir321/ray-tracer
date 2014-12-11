#include "Shape.h"
#include <iostream>

Shape::Shape()
{
}

Shape::Shape(Vector centre, RGBColour colour, double diffuseCoefficient, double reflectionCoefficient, double shininess)
{
	_centre = centre;
	_colour = colour;
	_diffuseCoefficient = diffuseCoefficient;
	_reflectionCoefficient = reflectionCoefficient;
	_shininess = shininess;
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

void Shape::SetDiffuseCoefficient(double diffuseCoefficient)
{
	_diffuseCoefficient = diffuseCoefficient;
}

void Shape::SetReflectionCoefficient(double reflectionCoefficient)
{
	_reflectionCoefficient = reflectionCoefficient;
}

void Shape::SetShininess(double shininess)
{
	_shininess = shininess;
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

double Shape::Shininess()
{
	return _shininess;
}
