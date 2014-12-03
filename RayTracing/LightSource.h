#ifndef LSOURCE_H
#define LSOURCE_H

#include "Vector.h"
#include "EasyBMP.h"

class LightSource
{
public :
	LightSource();
	LightSource(Vector position, RGBApixel colour);
	~LightSource(); 
	Vector GetPosition();
private :
	Vector _position;
	RGBApixel _colour;
};

#endif
