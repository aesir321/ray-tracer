#include "LightSource.h"

LightSource::LightSource()
{

}

LightSource::LightSource(Vector position, RGBColour colour, double specularIntensity, double diffuseIntensity)
{
	_position = position;
	_colour = colour;
	_specularIntensity = specularIntensity;
	_diffuseIntensity = diffuseIntensity;
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

double LightSource::SpecularIntensity()
{
	return _specularIntensity;
}

double LightSource::DiffuseIntensity()
{
	return _diffuseIntensity;
}