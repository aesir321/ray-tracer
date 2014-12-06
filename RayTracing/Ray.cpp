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

RGBColour Ray::Illumination(std::vector<LightSource> lightSources, RGBColour shapeColour, double diffuseCoefficient)
{
	double gamma = 1;
	double illumination = 0.0;
	RGBColour colour(0,0,0);

	for (int i = 0; i < lightSources.size(); i++)
	{
		Vector rayToSource = (lightSources.at(i).GetPosition() - _origin).UnitVector();
		illumination = rayToSource.ScalarProduct(_direction.UnitVector());

		if (illumination <= 0)
		{
			continue;
		}

		illumination = pow(illumination, gamma);

		colour = (shapeColour * illumination * diffuseCoefficient) + (shapeColour * lightSources.at(i).AmbientCoefficient()) + (shapeColour * lightSources.at(i).Colour() * illumination);
	}

	return colour;
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
