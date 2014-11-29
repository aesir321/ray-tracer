#include "Ray.h"

Ray::Ray()
{
  _x0 = 0;
  _y0 = 0;
  -z0 = 0;
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
  return 0.0;
}

