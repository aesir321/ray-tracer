#include "Ray.h"
#include "math.h"

Ray::Ray()
{
	Vector origin(0, 0, 0, true);
	Vector direction(0, 0, 0, true);
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
	Ray reflectedRay(_direction.UnitVector(), 
					RayLine()
					- surfaceNormal
					.MultiplyScalar(RayLine()
					.ScalarProduct(surfaceNormal))
					.MultiplyScalar(2));		
	return reflectedRay;
}

Ray Ray::Refraction()
{
  return Ray();
}

double Ray::Illumination(LightSource lightSource, Vector surfaceNormal)
{
	double gamma = 1.0;
	Vector reflectedRay = lightSource.GetPosition() - RayLine();
	double illumination = surfaceNormal.ScalarProduct(reflectedRay.UnitVector());
	if (illumination == -1)
	{
		illumination = 0.0;
	}
	illumination = pow(illumination, gamma);	
	
	return illumination;
}

Vector Ray::Direction()
{
  return _direction;
}

Vector Ray::Origin()
{
  return _origin;
}

Vector Ray::RayLine()
{
	return _origin + _direction;
}
