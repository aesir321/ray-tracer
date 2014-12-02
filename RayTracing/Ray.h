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
  double Illumination(LightSource lightsource, Vector surfaceNormal);
  Vector Direction();
  Vector Origin();
  Vector RayLine();

 private :
  Vector _direction;
  Vector _origin;

};
#endif
