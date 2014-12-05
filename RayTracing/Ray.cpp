#include "Ray.h"
#include "math.h"
#include <iostream>
#include <fstream>
#include <vector>

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

RGBColour Ray::Illumination(std::vector<LightSource> lightSources)
{
	double gamma = 1.0;
	double illumination = 0.0;
	RGBColour rgbColour;
	for (int i = 0; i < lightSources.size(); i++)
	{
		Vector rayToSource = (lightSources.at(i).GetPosition() - _origin).UnitVector();
		illumination += rayToSource.UnitVector().ScalarProduct(_direction.UnitVector()); //Is it additive?

		if (illumination < 0)
		{
			illumination = 0.0;
		}
		illumination = pow(illumination, gamma);
		rgbColour = lightSources.at(i).Colour() * illumination;
	}
	return rgbColour;

	/*if (illumination > 0)	{
		std::ofstream file;
		file.open("log.txt", std::ios_base::app);
		file << "rayToSource: (" << rayToSource.GetFirstComponent() << ", " << rayToSource.GetSecondComponent() << ", " << rayToSource.GetThirdComponent() << ")" << std::endl;
		file << "illumination: " << illumination << std::endl;
	}*/
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
