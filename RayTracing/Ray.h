#ifndef RAY_H
#define RAY_H

#include "Vector.h"
#include "LightSource.h"

class Ray
{
 public :
  Ray();
  Ray(Vector origin, Vector direction);
  ~Ray();
  Ray Reflection(Vector surfaceNormal);
  Ray Refraction();
  RGBColour Illumination(LightSource lightsource);
  Vector Direction();
  Vector Origin();
  Ray RayLine(double scalar);

 private :
  Vector _direction;
  Vector _origin;

};
#endif
