#include "LightSource.h"

LightSource::LightSource()
{

}

LightSource::LightSource(Vector position, RGBApixel colour)
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