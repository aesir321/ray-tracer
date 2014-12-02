#ifndef LSOURCE_H
#define LSOURCE_H

#include "Vector.h"

class LightSource
{
public :
	LightSource();
	LightSource(Vector position, double colour);
	~LightSource(); 
	Vector GetPosition();
private :
	Vector _position;
	double _colour;
};

#endif
