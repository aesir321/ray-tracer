#ifndef RAY_H
#define RAY_H

#include "Vector.h"
#include "LightSource.h"
#include <vector>
#include "../EasyBMP/EasyBMP.h"

class Ray
{
public:

	Ray();
	Ray(Vector origin, Vector direction);
	~Ray();

	Ray Reflection(Vector surfaceNormal);
	Ray Refraction();
	RGBColour Illumination(std::vector<LightSource> lightSources, RGBColour colour, double diffuseCoefficient);
	Vector Direction();
	Vector Origin();
	Ray RayLine(double scalar);

private:

	Vector _direction;
	Vector _origin;

};
#endif
