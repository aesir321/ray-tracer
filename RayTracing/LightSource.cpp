#include "LightSource.h"

LightSource::LightSource()
{

}

LightSource::LightSource(double coord1, double coord2, double coord3, bool cartesian)
{
	_coord1 = coord1;
	_coord2 = coord2;
	_coord3 = coord3;
	_cartesian = cartesian;
}

LightSource::~LightSource()
{

}