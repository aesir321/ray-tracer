#include "Ray.h"
#include "math.h"

Ray::Ray()
{
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

Ray Ray::Reflection(Vector surfaceNormal)
{
	Vector vector(_coord1, _coord2, _coord3, _cartesian);
	vector.SubtractScalar(vector.ScalarProduct(vector.MultiplyScalar(vector.ScalarProduct(surfaceNormal))));

	Ray ray(vector.GetFirstComponent(), vector.GetSecondComponent(), vector.GetThirdComponent(), true);

	return ray;
}

Ray Ray::Refraction()
{
  return Ray();
}

double Ray::Illumination(Ray reflectedRay, LightSource lightSource, Vector surfaceNormal)//Does it make sense for this to be here?  Illumination could be on the scene?
{
	double gamma = 1.0; //Where should this be set?
	Vector reflectionToSourceDirection = lightSource - reflectedRay;
	return abs(pow(reflectionToSourceDirection.ScalarProduct(surfaceNormal), gamma)); //Abs here as intensity is always +?  Not dependent on direction.
}

Vector Ray::Direction()
{
  return Vector();
}

