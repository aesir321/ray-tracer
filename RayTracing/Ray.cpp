#include "Ray.h"
#include "math.h"

Ray::Ray()
{
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
	Vector reflectedRay = lightSource.GetPosition();// - RayLine();
	double illumination = pow(1-surfaceNormal.ScalarProduct(reflectedRay.UnitVector()), 2);
	
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
