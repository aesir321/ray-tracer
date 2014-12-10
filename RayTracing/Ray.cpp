#include "Ray.h"

Ray::Ray()
{
	Vector origin(0, 0, 0);
	Vector direction(0, 0, 0);
	_origin = origin;
	_direction = direction;
}

Ray::Ray(Vector origin, Vector direction)
{
  _origin = origin;
  _direction = direction;
}

Ray::~Ray()
{

}

Ray Ray::Reflection(Vector surfaceNormal)
{	
	double temp = 2.0 * _direction.ScalarProduct(surfaceNormal);
	Vector temp2 = surfaceNormal * temp;

	Ray reflectedRay(_direction, _direction - temp2);
	return reflectedRay;
}

Ray Ray::Refraction()
{
  return Ray();
}

Vector Ray::Direction()
{
  return _direction;
}

Vector Ray::Origin()
{
  return _origin;
}

Ray Ray::RayLine(double scalar)
{
	Ray ray(_origin, _direction.UnitVector() * scalar);
	return ray;
}
