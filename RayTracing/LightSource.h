#ifndef LSOURCE_H
#define LSOURCE_H

#include "Vector.h"

class LightSource : public Vector
{
public :
	LightSource();
	LightSource(double coord1, double coord2, double coord3, bool cartesian);
	~LightSource();
};

#endif LSOURCE_H