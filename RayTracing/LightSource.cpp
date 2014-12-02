#include "LightSource.h"

LightSource::LightSource()
{

}

LightSource::LightSource(Vector position, double colour)
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