#ifndef LSOURCE_H
#define LSOURCE_H

#include "Vector.h"
#include "RGBColour.h"

class LightSource
{
public :
	LightSource();
	LightSource(Vector position, RGBColour colour, double ambientCoefficient);
	~LightSource(); 
	Vector GetPosition();
	RGBColour Colour();
	double AmbientCoefficient();

private :
	Vector _position;
	RGBColour _colour;
	double _ambientCoefficient;
};

#endif
