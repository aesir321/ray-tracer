#include "Ray.h"
#include "math.h"
#include <iostream>
#include <fstream>

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
	double temp = 2.0 * _direction.ScalarProduct(surfaceNormal); //overload *
	Vector temp2 = surfaceNormal.MultiplyScalar(temp);

	Ray reflectedRay(_direction, _direction - temp2);
	return reflectedRay;
}

Ray Ray::Refraction()
{
  return Ray();
}

RGBColour Ray::Illumination(LightSource lightSource)
{
	double gamma = 1.0;
	Vector rayToSource = (lightSource.GetPosition() - _origin).UnitVector();

	double illumination = rayToSource.UnitVector().ScalarProduct(_direction.UnitVector());

	/*if (illumination > 0)	{
		std::ofstream file;
		file.open("log.txt", std::ios_base::app);
		file << "rayToSource: (" << rayToSource.GetFirstComponent() << ", " << rayToSource.GetSecondComponent() << ", " << rayToSource.GetThirdComponent() << ")" << std::endl;
		file << "illumination: " << illumination << std::endl;
	}*/

	if (illumination < 0)
	{
		illumination = 0.0;
	}
	illumination = pow(illumination, gamma);	
	return lightSource.Colour() * illumination;
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
