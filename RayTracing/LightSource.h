#ifndef LSOURCE_H
#define LSOURCE_H

#include "Vector.h"
#include "RGBColour.h"

class LightSource
{
public :
	LightSource();
	LightSource(Vector position, RGBColour colour);
	~LightSource(); 
	Vector GetPosition();
	RGBColour LightSource::Colour();
private :
	Vector _position;
	RGBColour _colour;
};

#endif
