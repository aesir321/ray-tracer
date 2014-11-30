#include "Ray.h"

Ray::Ray()
{
  _x0 = 0;
  _y0 = 0;
  _z0 = 0;
}

Ray::Ray(double coord1, double coord2, double coord3, bool cartesian)
{
	_coord1 = coord1;
	_coord2 = coord2;
	_coord3 = coord3;
	_cartesian = cartesian;
}

Ray::~Ray()
{
}

Ray Ray::Reflection()
{
  return Ray();
}

Ray Ray::Refraction()
{
  return Ray();
}

double Ray::Illumination()
{
  return 0.0;
}

Vector Ray::Direction()
{
  return Vector();
}

