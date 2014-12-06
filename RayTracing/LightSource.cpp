#include "LightSource.h"

LightSource::LightSource()
{

}

LightSource::LightSource(Vector position, RGBColour colour, double ambientCoefficient)
{
	_position = position;
	_colour = colour;
	_ambientCoefficient = ambientCoefficient;
}

LightSource::~LightSource()
{
}

Vector LightSource::GetPosition()
{
	return _position;
}

RGBColour LightSource::Colour()
{
	return _colour;
}

double LightSource::AmbientCoefficient()
{
	return _ambientCoefficient;
}