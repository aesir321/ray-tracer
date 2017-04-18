#ifndef LSOURCE_H
#define LSOURCE_H

#include "Vector.h"
#include "../RGBColour.h"

class LightSource
{
public :

	LightSource();
	LightSource(Vector position, RGBColour colour, double specularIntensity, double diffuseIntensity);
	~LightSource(); 

	Vector GetPosition();
	RGBColour Colour();
	double SpecularIntensity();
	double DiffuseIntensity();

private :

	Vector _position;
	RGBColour _colour;
	double _specularIntensity;
	double _diffuseIntensity;
};

#endif
