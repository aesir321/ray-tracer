#include "LightSource.h"

LightSource::LightSource()
{

}

LightSource::LightSource(Vector position, RGBColour colour)
{
	_position = position;
	_colour = colour;
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